/*class TestRecoVertex
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2011/12/15 15:41:57 $
 *  $Revision: 1.2 $
 */
 
#include "TestRecoVertex.h"

using namespace edm;

TestRecoVertex::TestRecoVertex(const edm::ParameterSet& iPSet):  
  recoVertexCollection_(iPSet.getParameter<edm::InputTag>("recoVertexCollection"))
{    
}

TestRecoVertex::~TestRecoVertex() {}

void TestRecoVertex::beginJob()
{
}

void TestRecoVertex::endJob(){return;}
void TestRecoVertex::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void TestRecoVertex::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void TestRecoVertex::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  // Gather information on the reco::GenParticle collection
  edm::Handle<reco::VertexCollection> vtxCollection;
  iEvent.getByLabel(recoVertexCollection_, vtxCollection );

  edm::LogError("VertexSize") << (*vtxCollection).size();
  
}//analyze

