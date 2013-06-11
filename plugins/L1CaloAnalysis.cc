/*class L1CaloAnalysis
 *  
 *  Class to study L1 Calo triggers
 *
 *  $Date: 2013/05/29 16:22:41 $
 *  $Revision: 1.3 $
 *
 */

// framework & common header files
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"
#include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CLHEP/Vector/ThreeVector.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

class L1CaloAnalysis : public edm::EDAnalyzer
{

public:
  explicit L1CaloAnalysis(const edm::ParameterSet&);
  virtual ~L1CaloAnalysis();
  virtual void beginJob();
  virtual void endJob();  
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  virtual void endRun(const edm::Run&, const edm::EventSetup&);
  
private:
  
  edm::InputTag recoVertexCollection_;
  edm::InputTag caloRegionCollection_; 
  edm::InputTag ettCollection_; 
  edm::InputTag httCollection_; 
  edm::InputTag etmCollection_; 

  int vtxSel_;
  double etTh_;
  
  TH1F * hvtxHisto_;

  // Barrel

  TH1F * CRBmultiHisto_;
  TH1F * CRBtotETHisto_;
  TH1F * CRBtotSumETHisto_;
  TProfile* CRBtotSumETVSvtx_;

  // Endcap

  TH1F * CREmultiHisto_;
  TH1F * CREtotETHisto_;
  TH1F * CREtotSumETHisto_;
  TProfile* CREtotSumETVSvtx_;

  // Forward

  TH1F * CRFmultiHisto_;
  TH1F * CRFtotETHisto_;
  TH1F * CRFtotSumETHisto_;
  TProfile* CRFtotSumETVSvtx_;

  // Total 

  TH1F * L1ETTHisto_;
  TH1F * L1HTTHisto_;
  TH1F * L1ETMHisto_;
  TProfile* L1ETTVSvtx_;
  TProfile* L1HTTVSvtx_;
  TProfile* L1ETMVSvtx_;


  const int numvtx;
  const int nrankTh_;
  const float minRankTh_;

  edm::LumiReWeighting * theLumiW_;
  edm::InputTag puSummaryCollection_;
  std::string dataPUFile,mcPUFile,dataPUHisto,mcPUHisto;

  TH1F * truePUorigHisto_;
  TH1F * truePUreweHisto_;
  TH1F * weightHisto_;

  bool rewe_;

};

using namespace edm;

L1CaloAnalysis::L1CaloAnalysis(const edm::ParameterSet& iPSet):  
  recoVertexCollection_(iPSet.getParameter<edm::InputTag>("recoVertexCollection")),
  caloRegionCollection_(iPSet.getParameter<edm::InputTag>("caloRegionCollection")),
  ettCollection_(iPSet.getParameter<edm::InputTag>("ettCollection")),
  httCollection_(iPSet.getParameter<edm::InputTag>("httCollection")),
  etmCollection_(iPSet.getParameter<edm::InputTag>("etmCollection")),
  vtxSel_(iPSet.getParameter<int>("vtxSel")),
  etTh_(iPSet.getParameter<double>("etTh")),
  numvtx(60),nrankTh_(300),minRankTh_(10.)
{    

  edm::Service<TFileService> fs;

  hvtxHisto_ = fs->make<TH1F>( "vtx", "vertex ndof.gt.4 multiplicity", 100, 0., 100. ) ;

  CRBmultiHisto_ = fs->make<TH1F>( "CRBmulti", "L1 CaloRegion barrel multiplicity", 50, 0., 200. ); 

  CRBtotETHisto_ = fs->make<TH1F>( "CRBtotET", "L1 CaloRegion barrel tot E_T", 500, 0., 50. ); 
  CRBtotSumETHisto_ = fs->make<TH1F>( "CRBtotSumET", "L1 CaloRegion barrel tot sum E_T", 500, 0., 500. ); 
  CRBtotSumETVSvtx_ = fs->make<TProfile>( "CRBtotSumETVSvtx", "L1 CaloRegion barrel tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  CREmultiHisto_ = fs->make<TH1F>( "CREmulti", "L1 CaloRegion endcap multiplicity", 50, 0., 200. ); 

  CREtotETHisto_ = fs->make<TH1F>( "CREtotET", "L1 CaloRegion endcap tot E_T", 500, 0., 50. ); 
  CREtotSumETHisto_ = fs->make<TH1F>( "CREtotSumET", "L1 CaloRegion endcap tot sum E_T", 500, 0., 500. ); 
  CREtotSumETVSvtx_ = fs->make<TProfile>( "CREtotSumETVSvtx", "L1 CaloRegion endcap tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  CRFmultiHisto_ = fs->make<TH1F>( "CRFmulti", "L1 CaloRegion forward multiplicity", 50, 0., 200. ); 

  CRFtotETHisto_ = fs->make<TH1F>( "CRFtotET", "L1 CaloRegion forward tot E_T", 500, 0., 50. ); 
  CRFtotSumETHisto_ = fs->make<TH1F>( "CRFtotSumET", "L1 CaloRegion forward tot sum E_T", 500, 0., 500. ); 
  CRFtotSumETVSvtx_ = fs->make<TProfile>( "CRFtotSumETVSvtx", "L1 CaloRegion forward tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  L1ETTHisto_ = fs->make<TH1F>( "L1ETT", "L1 ETT", 500, 0., 1000. ); 
  L1HTTHisto_ = fs->make<TH1F>( "L1HTT", "L1 HTT", 500, 0., 1000. ); 
  L1ETMHisto_ = fs->make<TH1F>( "L1ETM", "L1 ETM", 500, 0., 1000. ); 

  L1ETTVSvtx_ = fs->make<TProfile>( "L1ETTVSvtx", "L1 ETT VS Vtx", numvtx, 0., (float)numvtx, 0., 1000.); 
  L1HTTVSvtx_ = fs->make<TProfile>( "L1HTTVSvtx", "L1 HTT VS Vtx", numvtx, 0., (float)numvtx, 0., 1000.); 
  L1ETMVSvtx_ = fs->make<TProfile>( "L1ETMVSvtx", "L1 ETM VS Vtx", numvtx, 0., (float)numvtx, 0., 1000.); 

  // Luminosity reweighting for simulation

  truePUorigHisto_ = fs->make<TH1F>( "truePUorig", "True PU distribution original", 100, 0., 100. );
  truePUreweHisto_ = fs->make<TH1F>( "truePUrewe", "True PU distribution reweighted", 100, 0., 100. );
  weightHisto_ = fs->make<TH1F>( "weight", "PU weight distribution", 100, 0., 10. );

  rewe_ = false;
  if ( iPSet.exists( "PUrew" ) ) {
    puSummaryCollection_ = (iPSet.getParameter<edm::ParameterSet>("PUrew")).getUntrackedParameter<edm::InputTag>("puSummaryCollection");
    dataPUFile = (iPSet.getParameter<edm::ParameterSet>("PUrew")).getUntrackedParameter<std::string>("dataPUFile");
    mcPUFile = (iPSet.getParameter<edm::ParameterSet>("PUrew")).getUntrackedParameter<std::string>("mcPUFile");
    dataPUHisto = (iPSet.getParameter<edm::ParameterSet>("PUrew")).getUntrackedParameter<std::string>("dataPUHisto");
    mcPUHisto = (iPSet.getParameter<edm::ParameterSet>("PUrew")).getUntrackedParameter<std::string>("mcPUHisto");
    theLumiW_ = new LumiReWeighting(mcPUFile,dataPUFile,mcPUHisto,dataPUHisto);
    rewe_ = true;
  }

}

L1CaloAnalysis::~L1CaloAnalysis() {}

void L1CaloAnalysis::beginJob()
{
}

void L1CaloAnalysis::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void L1CaloAnalysis::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void L1CaloAnalysis::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  // if simulation, perform pileup reweighting

  float theWeight = 1.;
  if ( ! iEvent.isRealData() && rewe_ ) {
    edm::Handle<std::vector< PileupSummaryInfo> > puSummary;
    iEvent.getByLabel(puSummaryCollection_, puSummary );
    
    std::vector<PileupSummaryInfo>::const_iterator PVI;

    float Tnpv = -1;
    for(PVI = puSummary->begin(); PVI != puSummary->end(); ++PVI) {

      int BX = PVI->getBunchCrossing();

      if(BX == 0) { 
        Tnpv = PVI->getTrueNumInteractions();
        continue;
      }

    }

    theWeight = theLumiW_->weight( Tnpv ); 

    truePUorigHisto_->Fill(Tnpv);
    truePUreweHisto_->Fill(Tnpv,theWeight);
    weightHisto_->Fill(theWeight);

  }

  // Start L1Calo analysis

  edm::Handle<reco::VertexCollection> vtxCollection;
  iEvent.getByLabel(recoVertexCollection_, vtxCollection );
  
  unsigned int nVtx = 0;
  for ( unsigned int iloop = 0; iloop < (*vtxCollection).size(); iloop++ ) {
    if ( (*vtxCollection)[iloop].ndof() > 4 ) { nVtx++; }
  }

  hvtxHisto_->Fill((float)nVtx,theWeight);

  edm::Handle<L1CaloRegionCollection> towers;
  iEvent.getByLabel(caloRegionCollection_,towers);

  std::vector<float> sumBCR(numvtx+1,0.);
  std::vector<float> sumECR(numvtx+1,0.);
  std::vector<float> sumFCR(numvtx+1,0.);

  double totSumBCR = 0.;
  double totSumECR = 0.;
  double totSumFCR = 0.;
  
  int nCRB =0;
  int nCRE= 0;
  int nCRF= 0;

  bool select((int)nVtx == vtxSel_);
  
  for (L1CaloRegionCollection::const_iterator r = towers->begin(); r != towers->end() ; ++r) {

    int ieta = r->gctEta();
    double rET = r->et();

    bool eneSelect( rET >= etTh_ );

    if ( ! eneSelect) { continue; }

    // HF

    if (r->isHf()) {
      if ( select ) {
        nCRF++;
        CRFtotETHisto_->Fill(rET, theWeight);
        totSumFCR += rET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumFCR[nVtx] += rET; 
      }
    } 
    
    // Endcap

    else if (ieta < 7 || ieta > 14) {
      if ( select ) {
        nCRE++;
        CREtotETHisto_->Fill(rET, theWeight);
        totSumECR += rET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumECR[nVtx] += rET; 
      }
    } 

    // Barrel 

    else {
      if ( select ) {
        nCRB++;
        CRBtotETHisto_->Fill(rET, theWeight);
        totSumBCR += rET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumBCR[nVtx] += rET; 
      }
    }    


  }

  if ( select ) {
    if ( nCRB > 0 ) { CRBmultiHisto_->Fill(nCRB,theWeight); }
    if ( nCRE > 0 ) { CREmultiHisto_->Fill(nCRE,theWeight); }
    if ( nCRF > 0 ) { CRFmultiHisto_->Fill(nCRF,theWeight); }
    if ( totSumBCR > 0. ) { CRBtotSumETHisto_->Fill(totSumBCR,theWeight); }
    if ( totSumECR > 0. ) { CRBtotSumETHisto_->Fill(totSumECR,theWeight); }
    if ( totSumFCR > 0. ) { CRBtotSumETHisto_->Fill(totSumFCR,theWeight); }
  }

  if ( (int)nVtx <= numvtx ) {
    if ( sumBCR[nVtx] > 0. ) { CRBtotSumETVSvtx_->Fill((float)nVtx,sumBCR[nVtx],theWeight); }
    if ( sumECR[nVtx] > 0. ) { CREtotSumETVSvtx_->Fill((float)nVtx,sumECR[nVtx],theWeight); }
    if ( sumFCR[nVtx] > 0. ) { CRFtotSumETVSvtx_->Fill((float)nVtx,sumFCR[nVtx],theWeight); }
  }


}//analyze

void L1CaloAnalysis::endJob(){

  return;

}


//define this as a plug-in
DEFINE_FWK_MODULE(L1CaloAnalysis);
