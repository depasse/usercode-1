#ifndef TESTHEPMC_H
#define TESTHEPMC_H

/*class TestHepMC
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

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"


class TestHepMC : public edm::EDAnalyzer
{
    public:
	explicit TestHepMC(const edm::ParameterSet&);
	virtual ~TestHepMC();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag hepmcCollection_;

	/// PDT table
	edm::ESHandle<HepPDT::ParticleDataTable> fPDGTable ;
	
};

#endif
