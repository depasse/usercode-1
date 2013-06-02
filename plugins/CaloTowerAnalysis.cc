/*class CaloTowerAnalysis
 *  
 *  Class to study ECAL response in Minimum Bias events
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

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include "CLHEP/Vector/ThreeVector.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

class CaloTowerAnalysis : public edm::EDAnalyzer
{

public:
  explicit CaloTowerAnalysis(const edm::ParameterSet&);
  virtual ~CaloTowerAnalysis();
  virtual void beginJob();
  virtual void endJob();  
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  virtual void endRun(const edm::Run&, const edm::EventSetup&);
  
private:
  
  edm::InputTag recoVertexCollection_;
  edm::InputTag caloTowerCollection_; 

  int vtxSel_;
  double etTh_,etEmTh_,etHadTh_;
  
  TH1F * hvtxHisto_;

  // Barrel

  TH1F * CTBmultiHisto_;
  TH1F * CTBemEHisto_;
  TH1F * CTBtotEHisto_;
  TH1F * CTBhadEHisto_;
  TH1F * CTBemETHisto_;
  TH1F * CTBtotETHisto_;
  TH1F * CTBhadETHisto_;
  TH1F * CTBemSumETHisto_;
  TH1F * CTBtotSumETHisto_;
  TH1F * CTBhadSumETHisto_;
  TProfile* CTBemSumETVSvtx_;
  TProfile* CTBhadSumETVSvtx_;
  TProfile* CTBtotSumETVSvtx_;

  // Endcap

  TH1F * CTEmultiHisto_;
  TH1F * CTEemEHisto_;
  TH1F * CTEtotEHisto_;
  TH1F * CTEhadEHisto_;
  TH1F * CTEemETHisto_;
  TH1F * CTEtotETHisto_;
  TH1F * CTEhadETHisto_;
  TH1F * CTEemSumETHisto_;
  TH1F * CTEtotSumETHisto_;
  TH1F * CTEhadSumETHisto_;
  TProfile* CTEemSumETVSvtx_;
  TProfile* CTEhadSumETVSvtx_;
  TProfile* CTEtotSumETVSvtx_;

  // Forward

  TH1F * CTFmultiHisto_;
  TH1F * CTFemEHisto_;
  TH1F * CTFtotEHisto_;
  TH1F * CTFhadEHisto_;
  TH1F * CTFemETHisto_;
  TH1F * CTFtotETHisto_;
  TH1F * CTFhadETHisto_;
  TH1F * CTFemSumETHisto_;
  TH1F * CTFtotSumETHisto_;
  TH1F * CTFhadSumETHisto_;
  TProfile* CTFemSumETVSvtx_;
  TProfile* CTFhadSumETVSvtx_;
  TProfile* CTFtotSumETVSvtx_;

  // Total 

  TH1F * CTemSumETHisto_;
  TH1F * CTtotSumETHisto_;
  TH1F * CThadSumETHisto_;
  TProfile* CTemSumETVSvtx_;
  TProfile* CThadSumETVSvtx_;
  TProfile* CTtotSumETVSvtx_;

  TH1F * CTemSumRank_;
  TH1F * CThadSumRank_;
  TH1F * CTtotSumRank_;

  const int numvtx;
  const int nrankTh_;
  const float minRankTh_;

};

using namespace edm;

CaloTowerAnalysis::CaloTowerAnalysis(const edm::ParameterSet& iPSet):  
  recoVertexCollection_(iPSet.getParameter<edm::InputTag>("recoVertexCollection")),
  caloTowerCollection_(iPSet.getParameter<edm::InputTag>("caloTowerCollection")),
  vtxSel_(iPSet.getParameter<int>("vtxSel")),
  etTh_(iPSet.getParameter<double>("etTh")),
  etEmTh_(iPSet.getParameter<double>("etEmTh")),
  etHadTh_(iPSet.getParameter<double>("etHadTh")),
  numvtx(60),nrankTh_(300),minRankTh_(10.)
{    

  edm::Service<TFileService> fs;

  hvtxHisto_ = fs->make<TH1F>( "vtx", "vertex ndof.gt.4 multiplicity", 100, 0., 100. ) ;

  CTBmultiHisto_ = fs->make<TH1F>( "CTBmulti", "CaloTower barrel multiplicity", 60, 0., 3000. ); 

  CTBemEHisto_ = fs->make<TH1F>( "CTBemE", "CaloTower barrel em energy", 100, 0., 100. ); 
  CTBhadEHisto_ = fs->make<TH1F>( "CTBhadE", "CaloTower barrel had energy", 100, 0., 100. ); 
  CTBtotEHisto_ = fs->make<TH1F>( "CTBtotE", "CaloTower barrel tot energy", 100, 0., 100. ); 
  CTBemETHisto_ = fs->make<TH1F>( "CTBemET", "CaloTower barrel em E_T", 500, 0., 50. ); 
  CTBhadETHisto_ = fs->make<TH1F>( "CTBhadET", "CaloTower barrel had E_T", 500, 0., 50. ); 
  CTBtotETHisto_ = fs->make<TH1F>( "CTBtotET", "CaloTower barrel tot E_T", 500, 0., 50. ); 
  CTBemSumETHisto_ = fs->make<TH1F>( "CTBemSumET", "CaloTower barrel em sum E_T", 500, 0., 500. ); 
  CTBhadSumETHisto_ = fs->make<TH1F>( "CTBhadSumET", "CaloTower barrel had sum E_T", 500, 0., 500. ); 
  CTBtotSumETHisto_ = fs->make<TH1F>( "CTBtotSumET", "CaloTower barrel tot sum E_T", 500, 0., 500. ); 

  CTBemSumETVSvtx_ = fs->make<TProfile>( "CTBemSumETVSvtx", "CaloTower barrel em sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  CTBhadSumETVSvtx_ = fs->make<TProfile>( "CTBhadSumETVSvtx", "CaloTower barrel had sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  CTBtotSumETVSvtx_ = fs->make<TProfile>( "CTBtotSumETVSvtx", "CaloTower barrel tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  CTEmultiHisto_ = fs->make<TH1F>( "CTEmulti", "CaloTower endcap multiplicity", 60, 0., 3000. ); 

  CTEemEHisto_ = fs->make<TH1F>( "CTEemE", "CaloTower endcap em energy", 100, 0., 100. ); 
  CTEhadEHisto_ = fs->make<TH1F>( "CTEhadE", "CaloTower endcap had energy", 100, 0., 100. ); 
  CTEtotEHisto_ = fs->make<TH1F>( "CTEtotE", "CaloTower endcap tot energy", 100, 0., 100. ); 
  CTEemETHisto_ = fs->make<TH1F>( "CTEemET", "CaloTower endcap em E_T", 500, 0., 50. ); 
  CTEhadETHisto_ = fs->make<TH1F>( "CTEhadET", "CaloTower endcap had E_T", 500, 0., 50. ); 
  CTEtotETHisto_ = fs->make<TH1F>( "CTEtotET", "CaloTower endcap tot E_T", 500, 0., 50. ); 
  CTEemSumETHisto_ = fs->make<TH1F>( "CTEemSumET", "CaloTower endcap em sum E_T", 500, 0., 500. ); 
  CTEhadSumETHisto_ = fs->make<TH1F>( "CTEhadSumET", "CaloTower endcap had sum E_T", 500, 0., 500. ); 
  CTEtotSumETHisto_ = fs->make<TH1F>( "CTEtotSumET", "CaloTower endcap tot sum E_T", 500, 0., 500. ); 

  CTEemSumETVSvtx_ = fs->make<TProfile>( "CTEemSumETVSvtx", "CaloTower endcap em sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  CTEhadSumETVSvtx_ = fs->make<TProfile>( "CTEhadSumETVSvtx", "CaloTower endcap had sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  CTEtotSumETVSvtx_ = fs->make<TProfile>( "CTEtotSumETVSvtx", "CaloTower endcap tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  CTFmultiHisto_ = fs->make<TH1F>( "CTFmulti", "CaloTower forward multiplicity", 60, 0., 3000. ); 

  CTFemEHisto_ = fs->make<TH1F>( "CTFemE", "CaloTower forward em energy", 100, 0., 100. ); 
  CTFhadEHisto_ = fs->make<TH1F>( "CTFhadE", "CaloTower forward had energy", 100, 0., 100. ); 
  CTFtotEHisto_ = fs->make<TH1F>( "CTFtotE", "CaloTower forward tot energy", 100, 0., 100. ); 
  CTFemETHisto_ = fs->make<TH1F>( "CTFemET", "CaloTower forward em E_T", 500, 0., 50. ); 
  CTFhadETHisto_ = fs->make<TH1F>( "CTFhadET", "CaloTower forward had E_T", 500, 0., 50. ); 
  CTFtotETHisto_ = fs->make<TH1F>( "CTFtotET", "CaloTower forward tot E_T", 500, 0., 50. ); 
  CTFemSumETHisto_ = fs->make<TH1F>( "CTFemSumET", "CaloTower forward em sum E_T", 500, 0., 500. ); 
  CTFhadSumETHisto_ = fs->make<TH1F>( "CTFhadSumET", "CaloTower forward had sum E_T", 500, 0., 500. ); 
  CTFtotSumETHisto_ = fs->make<TH1F>( "CTFtotSumET", "CaloTower forward tot sum E_T", 500, 0., 500. ); 

  CTFemSumETVSvtx_ = fs->make<TProfile>( "CTFemSumETVSvtx", "CaloTower forward em sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  CTFhadSumETVSvtx_ = fs->make<TProfile>( "CTFhadSumETVSvtx", "CaloTower forward had sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  CTFtotSumETVSvtx_ = fs->make<TProfile>( "CTFtotSumETVSvtx", "CaloTower forward tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  CTemSumETHisto_ = fs->make<TH1F>( "CTemSumET", "CaloTower all em sum E_T", 500, 0., 1000. ); 
  CThadSumETHisto_ = fs->make<TH1F>( "CThadSumET", "CaloTower all had sum E_T", 500, 0., 1000. ); 
  CTtotSumETHisto_ = fs->make<TH1F>( "CTtotSumET", "CaloTower all tot sum E_T", 500, 0., 1000. ); 

  CTemSumETVSvtx_ = fs->make<TProfile>( "CTemSumETVSvtx", "CaloTower all em sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 1000.); 
  CThadSumETVSvtx_ = fs->make<TProfile>( "CThadSumETVSvtx", "CaloTower all had sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 1000.); 
  CTtotSumETVSvtx_ = fs->make<TProfile>( "CTtotSumETVSvtx", "CaloTower all tot sum ET VS Vtx", numvtx, 0., (float)numvtx, 0., 1000.); 

  float maxRankTh_ = minRankTh_+(float)nrankTh_ ;

  CTemSumRank_ = fs->make<TH1F>( "CTemSumRank", "number of events passing sumET em threshold", nrankTh_, minRankTh_, maxRankTh_  ); 
  CThadSumRank_ = fs->make<TH1F>( "CThadSumRank", "number of events passing sumET had threshold", nrankTh_, minRankTh_, maxRankTh_ ); 
  CTtotSumRank_ = fs->make<TH1F>( "CTtotSumRank", "number of events passing sumET tot threshold", nrankTh_, minRankTh_, maxRankTh_ ); 

}

CaloTowerAnalysis::~CaloTowerAnalysis() {}

void CaloTowerAnalysis::beginJob()
{
}

void CaloTowerAnalysis::endJob(){return;}
void CaloTowerAnalysis::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void CaloTowerAnalysis::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void CaloTowerAnalysis::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  edm::Handle<reco::VertexCollection> vtxCollection;
  iEvent.getByLabel(recoVertexCollection_, vtxCollection );
  
  unsigned int nVtx = 0;
  for ( unsigned int iloop = 0; iloop < (*vtxCollection).size(); iloop++ ) {
    if ( (*vtxCollection)[iloop].ndof() > 4 ) { nVtx++; }
  }

  hvtxHisto_->Fill((float)nVtx);

  edm::Handle<CaloTowerCollection> towers;
  iEvent.getByLabel(caloTowerCollection_,towers);
  CaloTowerCollection::const_iterator cal;

  std::vector<float> sumBEmET(numvtx+1,0.);
  std::vector<float> sumBHadET(numvtx+1,0.);
  std::vector<float> sumBTotET(numvtx+1,0.);

  std::vector<float> sumEEmET(numvtx+1,0.);
  std::vector<float> sumEHadET(numvtx+1,0.);
  std::vector<float> sumETotET(numvtx+1,0.);

  std::vector<float> sumFEmET(numvtx+1,0.);
  std::vector<float> sumFHadET(numvtx+1,0.);
  std::vector<float> sumFTotET(numvtx+1,0.);

  std::vector<float> sumEmET(numvtx+1,0.);
  std::vector<float> sumHadET(numvtx+1,0.);
  std::vector<float> sumTotET(numvtx+1,0.);

  double emSumBET = 0.;
  double hadSumBET = 0.;
  double totSumBET = 0.;
  
  double emSumEET = 0.;
  double hadSumEET = 0.;
  double totSumEET = 0.;
  
  double emSumFET = 0.;
  double hadSumFET = 0.;
  double totSumFET = 0.;
  
  double emSumET = 0.;
  double hadSumET = 0.;
  double totSumET = 0.;

  int nCTB =0;
  int nCTE= 0;
  int nCTF= 0;

  bool select((int)nVtx == vtxSel_);
  
  for (CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end() ; ++cal) {

    double emE = cal->emEnergy();
    double hadE = cal->hadEnergy();
    double totE = cal->energy();
    double emET = cal->emEt();
    double hadET = cal->hadEt();
    double totET = cal->et();

    //    std::cout << "CT Energy " << emE << " " << hadE << " " << totE << std::endl; 
    //    std::cout << "CT ET     " << emET << " " << hadET << " " << totET << std::endl; 

    bool eneSelect(totET >= etTh_ && emET >= etEmTh_ && hadET >= etHadTh_);

    if ( ! eneSelect) { continue; }

    if ( std::fabs(cal->eta()) <= 3. ) {
      if ( select ) {
        emSumET += emET;
        hadSumET += hadET;
        totSumET += totET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumEmET[nVtx] += emET; 
        sumHadET[nVtx] += hadET; 
        sumTotET[nVtx] += totET; 
      }
    }
    
    if ( std::fabs(cal->eta()) <= 1.48 ) {
      if ( select ) {
        nCTB++;
        CTBemEHisto_->Fill(emE);
        CTBhadEHisto_->Fill(hadE);
        CTBtotEHisto_->Fill(totE);
        CTBemETHisto_->Fill(emET);
        CTBhadETHisto_->Fill(hadET);
        CTBtotETHisto_->Fill(totET);
        emSumBET += emET;
        hadSumBET += hadET;
        totSumBET += totET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumBEmET[nVtx] += emET; 
        sumBHadET[nVtx] += hadET; 
        sumBTotET[nVtx] += totET; 
      }
    }
    else if ( std::fabs(cal->eta()) > 1.48 && std::fabs(cal->eta()) <= 3.) {
      if ( select ) {
        nCTE++;
        CTEemEHisto_->Fill(emE);
        CTEhadEHisto_->Fill(hadE);
        CTEtotEHisto_->Fill(totE);
        CTEemETHisto_->Fill(emET);
        CTEhadETHisto_->Fill(hadET);
        CTEtotETHisto_->Fill(totET);
        emSumEET += emET;
        hadSumEET += hadET;
        totSumEET += totET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumEEmET[nVtx] += emET; 
        sumEHadET[nVtx] += hadET; 
        sumETotET[nVtx] += totET; 
      }
    }
    else {
      if ( select ) {
        nCTF++;
        CTFemEHisto_->Fill(emE);
        CTFhadEHisto_->Fill(hadE);
        CTFtotEHisto_->Fill(totE);
        CTFemETHisto_->Fill(emET);
        CTFhadETHisto_->Fill(hadET);
        CTFtotETHisto_->Fill(totET);
        emSumFET += emET;
        hadSumFET += hadET;
        totSumFET += totET;
      }
      if ( (int)nVtx <= numvtx ) {
        sumFEmET[nVtx] += emET; 
        sumFHadET[nVtx] += hadET; 
        sumFTotET[nVtx] += totET; 
      }
    }

  }

  if ( select ) {
    if ( nCTB > 0 ) { CTBmultiHisto_->Fill(nCTB); }
    if ( nCTE > 0 ) { CTEmultiHisto_->Fill(nCTE); }
    if ( nCTF > 0 ) { CTFmultiHisto_->Fill(nCTF); }
    if ( emSumBET > 0. ) { CTBemSumETHisto_->Fill(emSumBET); }
    if ( hadSumBET > 0. ) { CTBhadSumETHisto_->Fill(hadSumBET); }
    if ( totSumBET > 0. ) { CTBtotSumETHisto_->Fill(totSumBET); }
    if ( emSumEET > 0. ) { CTEemSumETHisto_->Fill(emSumEET); }
    if ( hadSumEET > 0. ) { CTEhadSumETHisto_->Fill(hadSumEET); }
    if ( totSumEET > 0. ) { CTEtotSumETHisto_->Fill(totSumEET); }
    if ( emSumFET > 0. ) { CTFemSumETHisto_->Fill(emSumFET); }
    if ( hadSumFET > 0. ) { CTFhadSumETHisto_->Fill(hadSumFET); }
    if ( totSumFET > 0. ) { CTFtotSumETHisto_->Fill(totSumFET); }
    if ( emSumET > 0. ) { CTemSumETHisto_->Fill(emSumET); }
    if ( hadSumET > 0. ) { CThadSumETHisto_->Fill(hadSumET); }
    if ( totSumET > 0. ) { CTtotSumETHisto_->Fill(totSumET); }
    
    for ( int irank = 0; irank < nrankTh_; irank++ ) {
      float threshold = minRankTh_+(float)irank;
      if ( emSumET > threshold ) { CTemSumRank_->Fill(threshold+0.5); }
      if ( hadSumET > threshold ) { CThadSumRank_->Fill(threshold+0.5); }
      if ( totSumET > threshold ) { CTtotSumRank_->Fill(threshold+0.5); }
    }
  }

  if ( (int)nVtx <= numvtx ) {
    if ( sumBEmET[nVtx] > 0. ) { CTBemSumETVSvtx_->Fill((float)nVtx,sumBEmET[nVtx]); }
    if ( sumBHadET[nVtx] > 0. ) { CTBhadSumETVSvtx_->Fill((float)nVtx,sumBHadET[nVtx]); }
    if ( sumBTotET[nVtx] > 0. ) { CTBtotSumETVSvtx_->Fill((float)nVtx,sumBTotET[nVtx]); }
    if ( sumEEmET[nVtx] > 0. ) { CTEemSumETVSvtx_->Fill((float)nVtx,sumEEmET[nVtx]); }
    if ( sumEHadET[nVtx] > 0. ) { CTEhadSumETVSvtx_->Fill((float)nVtx,sumEHadET[nVtx]); }
    if ( sumETotET[nVtx] > 0. ) { CTEtotSumETVSvtx_->Fill((float)nVtx,sumETotET[nVtx]); }
    if ( sumFEmET[nVtx] > 0. ) { CTFemSumETVSvtx_->Fill((float)nVtx,sumFEmET[nVtx]); }
    if ( sumFHadET[nVtx] > 0. ) { CTFhadSumETVSvtx_->Fill((float)nVtx,sumFHadET[nVtx]); }
    if ( sumFTotET[nVtx] > 0. ) { CTFtotSumETVSvtx_->Fill((float)nVtx,sumFTotET[nVtx]); }
    if ( sumEmET[nVtx] > 0. ) { CTemSumETVSvtx_->Fill((float)nVtx,sumEmET[nVtx]); }
    if ( sumHadET[nVtx] > 0. ) { CThadSumETVSvtx_->Fill((float)nVtx,sumHadET[nVtx]); }
    if ( sumTotET[nVtx] > 0. ) { CTtotSumETVSvtx_->Fill((float)nVtx,sumTotET[nVtx]); }
  }


}//analyze


//define this as a plug-in
DEFINE_FWK_MODULE(CaloTowerAnalysis);
