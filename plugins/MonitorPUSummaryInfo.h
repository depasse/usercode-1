#ifndef MONITORPUSUMMARYINFO_H
#define MONITORPUSUMMARYINFO_H

/*class MonitorPUSummaryInfo
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2013/02/02 22:10:28 $
 *  $Revision: 1.3 $
 *
 */

// framework & common header files
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

class MonitorPUSummaryInfo : public edm::EDAnalyzer
{
    public:
	explicit MonitorPUSummaryInfo(const edm::ParameterSet&);
	virtual ~MonitorPUSummaryInfo();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag puSummaryCollection_;

    TH1F * nBXHisto_;
    TH1F * nPUHisto_;
    TH1F * nTruePUHisto_;
    TH1F * zPUHisto_; 
    TProfile * nPUvsBXHisto_;
    TProfile * nTruePUvsBXHisto_;

    TH1F * nTruem1Histo_ ;
    TH1F * nTrue0Histo_ ;
    TH1F * nTruep1Histo_ ;
    TH1F * nPUm1Histo_ ;
    TH1F * nPU0Histo_ ;
    TH1F * nPUp1Histo_ ;

    TH2F * nPUvsTruePUHisto_ ;

};

#endif
