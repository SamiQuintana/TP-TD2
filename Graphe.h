

#ifndef TP2_GRAPHE_GRAPHE_H
#define TP2_GRAPHE_GRAPHE_H

#include <iostream>
#include "Sommet.h"

class Graphe {

private:
    bool m_estOriente{};
    std::vector< Sommet*> m_sommets;

public:
    explicit Graphe(const std:: string& cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    std::vector<int> BFS(int numero_S0) const;
    std::vector<int> DFS(int numero_S0) const;
    void CompConnexe() ;

};


#endif //TP2_GRAPHE_GRAPHE_H
