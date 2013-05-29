/*class TestHepMC
 *  
 *  Class to fill dqm monitor elements from existing EDM file
 *
 *  $Date: 2013/04/12 07:13:05 $
 *  $Revision: 1.2 $
 */
 
#include "TestHepMC.h"

#include "CLHEP/Units/defs.h"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace edm;

TestHepMC::TestHepMC(const edm::ParameterSet& iPSet):  
  hepmcCollection_(iPSet.getParameter<edm::InputTag>("hepmcCollection"))
{    
}

TestHepMC::~TestHepMC() {}

void TestHepMC::beginJob()
{
}

void TestHepMC::endJob(){return;}
void TestHepMC::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
  ///Get PDT Table
  iSetup.getData( fPDGTable );
  return;
}
void TestHepMC::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void TestHepMC::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 
  ///Gathering the HepMCProduct information
  edm::Handle<HepMCProduct> evt;
  iEvent.getByLabel(hepmcCollection_, evt);

  //Get EVENT
  HepMC::GenEvent *myGenEvent = new HepMC::GenEvent(*(evt->GetEvent()));

  ///Bjorken variable from PDF
  //  HepMC::PdfInfo *pdf = myGenEvent->pdf_info();    

  //Looping through the VERTICES in the event
  HepMC::GenEvent::vertex_const_iterator vrtxBegin = myGenEvent->vertices_begin();
  HepMC::GenEvent::vertex_const_iterator vrtxEnd = myGenEvent->vertices_end();
  for(HepMC::GenEvent::vertex_const_iterator vrtxIt = vrtxBegin; vrtxIt!=vrtxEnd; ++vrtxIt)
    {
      ///Vertices
      HepMC::GenVertex *vrtx = *vrtxIt;
	
      ///loop on vertex particles
      HepMC::GenVertex::particles_out_const_iterator vrtxPtclBegin = vrtx->particles_out_const_begin();
      HepMC::GenVertex::particles_out_const_iterator vrtxPtclEnd = vrtx->particles_out_const_end();
      for(HepMC::GenVertex::particles_out_const_iterator vrtxPtclIt = vrtxPtclBegin; vrtxPtclIt != vrtxPtclEnd; ++vrtxPtclIt)
        {
          HepMC::GenParticle *vrtxPtcl = *vrtxPtclIt;
          if (vrtxPtcl->status() == 1){
          }
        }
    }//vertices

  
  int nReco = 0;
  double energy = 0.;
  double pxtot = 0.;
  double pytot = 0.;
  double pztot = 0.;
    
  ///Looping through the PARTICLES in the event
  HepMC::GenEvent::particle_const_iterator ptclBegin = myGenEvent->particles_begin();
  HepMC::GenEvent::particle_const_iterator ptclEnd = myGenEvent->particles_end();
  for(HepMC::GenEvent::particle_const_iterator ptclIt = ptclBegin; ptclIt!=ptclEnd; ++ptclIt)
    {
    
      ///Particles
      HepMC::GenParticle *ptcl = *ptclIt;
      int Id = ptcl->pdg_id(); // std::cout << Id << '\n'; 
      //      float Log_p = log10( ptcl->momentum().rho() );
      //      double charge = 999.;	// for the charge it's needed a HepPDT method
      //      const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(Id));
      //      if(PData==0) {
        //	    std::cout << "Unknown id = " << Id << '\n';
      //      }
      //      else
      //	    charge = PData->charge();

      ///Status statistics
      ///Stable particles
      if(ptcl->status() == 1){
        nReco++;
        energy += ptcl->momentum().e();
        pxtot += ptcl->momentum().px();
        pytot += ptcl->momentum().py();
        pztot += ptcl->momentum().pz();
        std::cout << "hepmc " << std::setw(14) << std::fixed << Id 
                  << std::setw(14) << std::fixed << ptcl->momentum().px() 
                  << std::setw(14) << std::fixed << ptcl->momentum().py() 
                  << std::setw(14) << std::fixed << ptcl->momentum().pz() 
                  << std::setw(14) << std::fixed << ptcl->momentum().e() << std::endl;
      }
	
    }//event particles

  std::cout << "# particle = " << nReco << std::endl;
  std::cout << "Status 1 total energy = " << energy << std::endl;
  std::cout << "Status 1 total px     = " << pxtot << std::endl;
  std::cout << "Status 1 total py     = " << pytot << std::endl;
  std::cout << "Status 1 total pz     = " << pztot << std::endl;

  delete myGenEvent;
}//analyze
