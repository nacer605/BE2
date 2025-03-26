#include "Aquarium.h"
#include "BestioleFactory.h"
#include "Milieu.h"


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


void Aquarium::run(BestioleFactory* Factory)
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

      flotte->Step(Factory);
      flotte->percussionBestiole();
      display( *flotte );
      wait( delay );
      flotte->Update();
   } // while
   std::cout<<"nombre bestioles gregaire : "<<flotte->nbrBestiolesGregaires<<std::endl;
   std::cout<<"nombre bestioles gregaires mortes : "<<flotte->nbrBestiolesGregairesMortes<<std::endl;
}
