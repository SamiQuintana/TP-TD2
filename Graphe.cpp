

#include "Graphe.h"
#include <fstream>
#include <queue>
#include <stack>

Graphe::Graphe(const std::string& cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if (!ifs){
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente; //m_estOrienté prends soit 0 ou 1
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    int taille;
    ifs >> taille;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    for(int i=0; i< ordre; i++){
        m_sommets.push_back(new Sommet(i)); ///prends en compte le nombre de sommet dans le graphe
    }
    int num1, num2;
    for(int i=0; i<taille; i++){
        ifs >> num1 >> num2;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture d'un arc/arrete."); ///Execute au moment de l execution
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]); ///num1 successeur de num2
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
    }

}

Graphe::~Graphe() {
    for (auto addSommet: m_sommets) { ///chaque cases possèdes une adresse de sommets qui seront detruit
        delete addSommet;
    }
}

void Graphe::afficher() const {
    std::cout << std::endl <<"Graphe ";
    std::cout << (m_estOriente ? " oriente" : "non oriente") << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Liste d'adjacence : " << std::endl;
    for(auto addrSommet : m_sommets){
        addrSommet-> afficher();
        std::cout << std::endl;
    }
}

std::vector<int> Graphe::BFS(int numero_S0) const {
    ///Tous les sommets sont blancs nn decouverts
    std::vector<int > couleurs((int) m_sommets.size(), 0);
    ///Creer une file vide
    std::queue<const Sommet*> file;
    std::vector<int > predecesseurs((int) m_sommets.size(), -1);
    ///Enfiler s0; s0 deviens gris
    file.push(m_sommets[numero_S0]);
    couleurs[numero_S0] = 1; // gris
    const Sommet* s; /// On ne modifie pas l'adresse de s.
    ///Tant que la file n'est pas vide
    while(!file.empty()){
        ///Defiler le prochain sommert s de la file
        s = file.front();
        file.pop();
        ///Pour chaque successeur s' blanc non decourt de s:
        for(auto succ: s->getSuccesseur()){
            if(couleurs[succ->getNumero()] == 0){
                ///Enfiler s'; s' deviens gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                ///Noter s est le predecesseur de s'
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        couleurs[s-> getNumero()] = 2; //noir

    }
    return predecesseurs;
}

std::vector<int> Graphe::DFS(int numero_S0) const {
    ///Tous les sommets sont blancs nn decouverts
    std::vector<int > couleurs((int) m_sommets.size(), 0);
    ///Creer une pile vide
    std::stack<const Sommet*> pile;
    std::vector<int > predecesseurs((int) m_sommets.size(), -1);
    ///Enfiler s0; s0 deviens gris
    pile.push(m_sommets[numero_S0]);
    couleurs[numero_S0] = 1; // gris
    const Sommet* s; /// On ne modifie pas l'adresse de s.
    ///Tant que la pile n'est pas vide
    while(!pile.empty()){
        ///Defiler le prochain sommet s de la pile
        s = pile.top();
        pile.pop();
        ///Pour chaque successeur s' blanc non decouvert de s:
        for(auto succ: s->getSuccesseur()){
            if(couleurs[succ->getNumero()] == 0){
                ///Enfiler s'; s' deviens gris
                pile.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                ///Noter s est le predecesseur de s'
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        couleurs[s-> getNumero()] = 2; //noir

    }
    return predecesseurs;
}

void Graphe::CompConnexe(){
    std::vector<int> couleurs( (int) m_sommets.size(), 0);
    std::cout <<"liste des composantes connexes : " << std::endl;
        for (auto s : m_sommets)
            if (couleurs [s->getNumero()] != 1){
                std::cout << " {";
                std::vector<int> arborescence_2 = BFS(s->getNumero());
                for (size_t i = 0; i<arborescence_2.size();i++){
                    if (i != s->getNumero()){
                        if(arborescence_2[i] != -1){
                            std::cout << i << " ";
                            couleurs[i]=1;
                        }
                    }

                }
                couleurs[s->getNumero()]=1;
                std::cout <<s->getNumero();
                std::cout<< "} ";
            }
}
/// ici présent le code DFS en récursif fonctionnel mais qui a des problemes pour s'afficher

/*
void DFS_recursif(int numero_S0) const;
void Graphe::DFS_recursif(int numero_S0) const {
    /// Tous les sommets sont blancs non découverts
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    /// On grise le sommet actuel
    couleurs[numero_S0] = 1;
    /// On crée le sommet du numéro correspondant
    Sommet s(numero_S0);
    /// Pour tous ses successeurs, on teste s'ils sont blanc, si oui alors on re effectue la procédure avec le sommet en question
    for(auto succ: s.getSuccesseur())
    {
        if(couleurs[succ->getNumero()] == 0)
        {
            DFS_recursif(succ->getNumero());
        }
    }

}
 */
