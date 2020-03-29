#include <iostream>
#include "Graphe.h"

void afficherParcours(size_t s0, const std::vector<int>& predecesseur){
    for (size_t i=0; i < predecesseur.size(); i++ ){
        if(i != s0){
            if(predecesseur[i] != -1){ //-1 pas accessible depuis s0
                std::cout << i << " <---- ";
                size_t j = predecesseur[i];
                while(j != s0){
                    std::cout << j << " <---- ";
                    j = predecesseur[j];
                }
                std::cout << j << std::endl;
            }
        }
    }
}


int main() {
    size_t s0 = 0;
    Graphe g{"../Graphe_NO"};
    std::vector<int> arborescence;
    std::vector<int> arborescence_2;
    g.afficher();


    std::cout << "DFS: Veuillez saisir le numero du sommet initial pour le parcours en profondeur : ";
    std::cin >> s0;
    arborescence = g.DFS(s0);
    std::cout << "Parcours en profondeur depuis " << s0 << "(DFS) : " << std::endl;
    afficherParcours(s0, arborescence);


    std::cout << "BFS: Veuillez saisir le numero du sommet initial pour le parcours en largeur : ";
    std::cin >> s0;
    arborescence_2 = g.BFS(s0);
    std::cout << "Parcours en largeur depuis " << s0 << "(BFS) : " << std::endl;
    afficherParcours(s0, arborescence_2);

    g.CompConnexe();
    return 0;
}
