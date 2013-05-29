
#include "LHEZdecayFilter.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include <iostream>

using namespace edm;
using namespace std;


LHEZdecayFilter::LHEZdecayFilter(const edm::ParameterSet& iConfig) :
  src_(iConfig.getParameter<InputTag>( "src" ) ),
  leptonID_(iConfig.getParameter<int>( "leptonID" ) ),
  verbose_(iConfig.getUntrackedParameter<bool>( "verbose","False" ) )
{
   //now do what ever initialization is needed

}


LHEZdecayFilter::~LHEZdecayFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
bool LHEZdecayFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   bool accepted = false;

   Handle<LHEEventProduct> evt;
   iEvent.getByLabel( src_, evt );

   const lhef::HEPEUP hepeup_ = evt->hepeup();

   const int nup_ = hepeup_.NUP; 
   const std::vector<int> idup_ = hepeup_.IDUP;
   const std::vector<lhef::HEPEUP::FiveVector> pup_ = hepeup_.PUP;

   unsigned int cLep = 0;
   int netCharge = 0; 

   for ( unsigned int icount = 0 ; icount < (unsigned int)nup_; icount++ ) {

     if ( std::abs(idup_[icount]) == leptonID_ ) { cLep++; netCharge += idup_[icount]; }
     
   }

   if ( cLep == 2 && netCharge == 0 ) { 
     accepted = true; 
     if (verbose_) {
       for ( unsigned int icount = 0 ; icount < (unsigned int)nup_; icount++ ) {
         std::cout << "# " << icount << " " << idup_[icount] << " " << (pup_[icount])[0] << " " << (pup_[icount])[1] << " " << (pup_[icount])[2] << " " << (pup_[icount])[3] << " " << (pup_[icount])[4] << std::endl;
       }
     }
   }

   if (accepted){
   return true; } else {return false;}

}

