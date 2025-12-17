#!/bin/bash

# ON SUPPOSE FICHIER S APPLEE WILDWATER

# aff dure totale en ms
duree_totale() {
    fin_tps=$(date +%s)
    r_duree=$((fin_tps - START_TIME))
    echo "La durée totale est : $((r_duree * 1000)) mili-seconde"
}

#aff une erreur et arrêter le script
fct_error() {
    echo "Erreur : $1" >&2
    duree_totale
    exit 1
}


# récupérer les arguments ecrit ds terlmianl
recup_arg() {
    if [ $# -lt 2 ]; then
        fct_error "Reesayer manque d'arguments"
    fi

    fichier_d="$1" #chemin du fichier
    Type="$2" #histo ou leaks
    Option="$3" # max src real id usine
    NB_ARG=$# #nb argument
}


# vérif la validité des arguments
arg_valid_T() {
    case "$Type" in
        histo)
            if [ "$NB_ARG" -ne 3 ]; then
                fct_error "Nombre d'arguments insuffisant pour histo !"
            fi
            if [ "$Option" != "max" ] && [ "$Option" != "src" ] && [ "$Option" != "real" ]; then
                fct_error "Option invalide (max | src | real)"
            fi
            ;;
        leaks)
            if [ "$NB_ARG" -ne 3 ]; then # le prog shell ne verifie pas si l' id existe ou pas !
                fct_error "Nombre d'arguments insuffisant pour leaks !"
            fi
            ;;
        *)
            fct_error "Type inconnu (histo | leaks)"
            ;;
    esac
}


# vérif l'existence/ lecrure fichier
verif_fichier() {
    if [ ! -f "$fichier_d" ]; then # si fichier
        fct_error "Fichier introuvable : ("
    fi

    if [ ! -r "$fichier_d" ]; then # si permission de le lire
        fct_error "Fichier non lisible"
    fi
}


# compiler le programme C avec make si nécessaire
fct_compilation() {
    if [ ! -x "./wildwater" ]; then # si permission de l'excuter
        echo "Compilation"
        make # commande de compilation automatique
        if [ $? -ne 0 ]; then # code de retour de make b
           fct_error "Mince, echec lors de la compilation"
        fi
    fi
}



crea_histo() {
    Fichier_sortie="histo_${Option}.dat"

    ./wildwater "$fichier_d" histo "$Option"
    if [ $? -ne 0 ]; then
        fct_error "Oups, erreur lors de la generation de l'histo"
    fi

    echo "Histogramme genere : $Fichier_sortie"
}

crea_leaks() {
    Fichier_sortie="leaks.dat"

    ./wildwater "$fichier_d" leaks "$Option" > "$Fichier_sortie"
    if [ $? -ne 0 ]; then
        fct_error "Oups, erreur lors du traitement de leaks"
    fi

    echo "Fichier leaks généré : $Fichier_sortie"
}

# lance caulcu de fuite


generation_image() {
    Fichier_data="histo_${Option}.dat"

    if [ ! -f "$Fichier_data" ]; then
        fct_error "Fichier pour la generation d'image introuvable : $Fichier_data"
    fi

    gnuplot << EOF
set terminal png size 900,600
set datafile separator ";"
set style fill solid
set grid
set xtics rotate by -45

# 50 plus petites usines
set output "${Fichier_data%.dat}_50_small.png"
set title "50 plus petites usines (${Option})"
set xlabel "Usines"
set ylabel "Volume"
plot "< tail -n +2 $Fichier_data | sort -t';' -k2,2n | head -n 50" \
     using 2:xtic(1) with boxes notitle

# 10 plus grandes usines
set output "${Fichier_data%.dat}_10_large.png"
set title "10 plus grandes usines (${Option})"
set xlabel "Usines"
set ylabel "Volume"
plot "< tail -n +2 $Fichier_data | sort -t';' -k2,2nr | head -n 10" \
     using 2:xtic(1) with boxes notitle
EOF

    if [ $? -ne 0 ]; then
        fct_error "Erreur lors de la génération des images"
    fi

    echo "Images générées à partir de $Fichier_data"
}

# dans le main
START_TIME=$(date +%s)

recup_arg "$@"
arg_valid_T
verif_fichier
fct_compilation

case "$Type" in
    histo)
        crea_histo
        generation_image
        ;;
    leaks)
        crea_leaks
        ;;
esac

duree_totale
exit 0