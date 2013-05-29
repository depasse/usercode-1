/*class MonitorRecoPU
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2011/12/15 16:08:18 $
 *  $Revision: 1.2 $
 */
 
#include "MonitorRecoPU.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

using namespace edm;

MonitorRecoPU::MonitorRecoPU(const edm::ParameterSet& iPSet):  
  recoVertexCollection_(iPSet.getParameter<edm::InputTag>("recoVertexCollection")),
  pixelClusterCollection_(iPSet.getParameter<edm::InputTag>("pixelClusterCollection"))
{    

  edm::Service<TFileService> fs;

  vtxHisto_ = fs->make<TH1F>( "vtx", "vertex ndof.gt.4 multiplicity", 100, 0., 100. ) ;
  pixcluHisto_ = fs->make<TH1F>( "pixclu", "pixel cluster multiplicity", 100, 0., 10000. ) ;
}

MonitorRecoPU::~MonitorRecoPU() {}

void MonitorRecoPU::beginJob()
{
}

void MonitorRecoPU::endJob(){return;}
void MonitorRecoPU::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void MonitorRecoPU::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void MonitorRecoPU::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  edm::Handle<reco::VertexCollection> vtxCollection;
  iEvent.getByLabel(recoVertexCollection_, vtxCollection );
  
  unsigned int nVtx = 0;
  for ( unsigned int iloop = 0; iloop < (*vtxCollection).size(); iloop++ ) {
    if ( (*vtxCollection)[iloop].ndof() > 4 ) { nVtx++; }
  }

  edm::Handle< edmNew::DetSetVector<SiPixelCluster> > pixcluCollection;
  iEvent.getByLabel(pixelClusterCollection_, pixcluCollection );
  
  unsigned int nPixClu = (*pixcluCollection).size();

  vtxHisto_->Fill((float)nVtx);
  pixcluHisto_->Fill((float)nPixClu);

  edm::LogInfo("RecoPUInfo") << iEvent.id() << " # Vtx = " << nVtx << " # SiPixClu = " << nPixClu ; 

}//analyze

