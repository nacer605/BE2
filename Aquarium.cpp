#include "Aquarium.h"
#include "BestioleFactory.h"
#include "Milieu.h"
#include <fstream>  // pour std::ofstream
#include <vector>
#include <string>


Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::genererFichierMetriques(const std::vector<int>& vecteur_bestioles_initiales) {
   std::ofstream fichier("metriques.txt");  // ouvre ou crée le fichier

   if (!fichier.is_open()) {
       std::cerr << "Erreur : impossible d'ouvrir le fichier des métriques." << std::endl;
       return;
   }

   std::vector<std::string> noms = {
       "Gregaire", "Kamikaze", "Peureuse", "Prevoyante", "Multi"
   };
   std::vector<int> mortes = {
       flotte->nbrBestiolesGregairesMortes,
       flotte->nbrBestiolesKamikazeMortes,
       flotte->nbrBestiolesPeureuseMortes,
       flotte->nbrBestiolesPrevoyantMortes,
       flotte->nbrBestiolesMultiMortes
   };

   for (size_t i = 0; i < noms.size(); ++i) {
       fichier << "Nombre bestioles " << noms[i] << " : " << vecteur_bestioles_initiales[i] << std::endl;
       fichier << "Nombre bestioles " << noms[i] << " mortes par collision : " << mortes[i] << std::endl;
   }

   fichier.close();  // toujours fermer proprement
}


void Aquarium::run(BestioleFactory* Factory,std::vector<int> vecteur_bestioles_initiales)
{

   cout << "running Aquarium" << endl;

   while ( ! is_closed() && flotte->nbBestioles() > 0 )
   {

      // cout << "iteration de la simulation" << endl;

      if ( is_key() ) {
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ) close();
      }

      flotte->Step(Factory,vecteur_bestioles_initiales);
      flotte->percussionBestiole();
      display( *flotte );
      wait( delay );
      flotte->Update();
   } // while
   std::cout<<"nombre bestioles gregaire : "<< vecteur_bestioles_initiales[0] <<std::endl;
   std::cout<<"nombre bestioles gregaires mortes par collision : "<<flotte->nbrBestiolesGregairesMortes<<std::endl;


   std::cout<<"nombre bestioles Kamikaze : "<<vecteur_bestioles_initiales[1]<<std::endl;
   std::cout<<"nombre bestioles Kamikaze mortes par collision : "<<flotte->nbrBestiolesKamikazeMortes<<std::endl;


   std::cout<<"nombre bestioles Peureuse : "<<vecteur_bestioles_initiales[2]<<std::endl;
   std::cout<<"nombre bestioles Peureuse mortes par collision : "<<flotte->nbrBestiolesPeureuseMortes<<std::endl;

   std::cout<<"nombre bestioles Prevoyantes : "<<vecteur_bestioles_initiales[3]<<std::endl;
   std::cout<<"nombre bestioles Prevoyantes mortes par collision : "<<flotte->nbrBestiolesPrevoyantMortes<<std::endl;

   std::cout<<"nombre bestioles Multi : "<<vecteur_bestioles_initiales[4]<<std::endl;
   std::cout<<"nombre bestioles Multi mortes par collision : "<<flotte->nbrBestiolesMultiMortes<<std::endl;


   genererFichierMetriques(vecteur_bestioles_initiales ) ;
}
