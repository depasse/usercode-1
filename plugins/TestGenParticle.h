#ifndef TESTGENPARICLE_H
#define TESTGENPARICLE_H

/*class TestGenParticle
 *  
 *  Class to fill Event Generator dqm monitor elements; works on HepMCProduct
 *
 *  $Date: 2011/09/22 12:49:30 $
 *  $Revision: 1.1 $
 *
 */

// framework & common header files
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Run.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"


class TestGenParticle : public edm::EDAnalyzer
{
    public:
	explicit TestGenParticle(const edm::ParameterSet&);
	virtual ~TestGenParticle();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag genparticleCollection_;
    edm::InputTag genjetCollection_;

    unsigned int verbosity_;

	/// PDT table
	edm::ESHandle<HepPDT::ParticleDataTable> fPDGTable ;
	

};

#endif
