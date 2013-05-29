/*class TestGenParticle
 *  
 *  Class to fill dqm monitor elements from existing EDM file
 *
 *  $Date: 2011/09/22 12:49:30 $
 *  $Revision: 1.1 $
 */
 
#include "TestGenParticle.h"

#include "CLHEP/Units/defs.h"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace edm;

TestGenParticle::TestGenParticle(const edm::ParameterSet& iPSet):  
  genparticleCollection_(iPSet.getParameter<edm::InputTag>("genparticleCollection")),
  verbosity_(iPSet.getUntrackedParameter<unsigned int>("verbosity",0))
{    
}

TestGenParticle::~TestGenParticle() {}

void TestGenParticle::beginJob()
{
}

void TestGenParticle::endJob(){return;}
void TestGenParticle::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
  ///Get PDT Table
  iSetup.getData( fPDGTable );
  return;
}
void TestGenParticle::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void TestGenParticle::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  unsigned int initSize = 1000;

  // Gather information on the reco::GenParticle collection
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genparticleCollection_, genParticles );
  
  std::vector<const reco::GenParticle*> particles;
  particles.reserve(initSize);
  float energy = 0.;
  float pxtot = 0.;
  float pytot = 0.;
  float pztot = 0.;
  for (reco::GenParticleCollection::const_iterator iter=genParticles->begin();iter!=genParticles->end();++iter){
    if ( (*iter).status() == 1) { 
      particles.push_back(&*iter); 
      if ( verbosity_ > 0 ) {
        std::cout << "reco  " << std::setw(14) << std::fixed << (*iter).pdgId() << std::setw(14) << std::fixed << (*iter).px() 
                  << std::setw(14) << std::fixed << (*iter).py() << std::setw(14) << std::fixed << (*iter).pz() << std::endl;
      }
      energy += std::sqrt( (*iter).px()*(*iter).px() + 
                           (*iter).py()*(*iter).py() + 
                           (*iter).pz()*(*iter).pz() + 
                           (*iter).mass()*(*iter).mass()) ; 
      pxtot += (*iter).px();
      pytot += (*iter).py();
      pztot += (*iter).pz();
    }
  }

  unsigned int nReco = particles.size();
  std::cout << "# particle = " << nReco << std::endl;
  std::cout << "Status 1 total energy = " << energy << std::endl;
  std::cout << "Status 1 total px     = " << pxtot << std::endl;
  std::cout << "Status 1 total py     = " << pytot << std::endl;
  std::cout << "Status 1 total pz     = " << pztot << std::endl;

}//analyze

