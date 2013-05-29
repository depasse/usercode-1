#ifndef TESTGENINFOPRODUCT_H
#define TESTGENINFOPRODUCT_H

/*class TestGenInfoProduct
 *  
 *  Class to dump Run and Event GEN level InfoProduct
 *
 *  $Date: 2012/10/05 12:51:52 $
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

#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

class TestGenInfoProduct : public edm::EDAnalyzer
{
    public:
	explicit TestGenInfoProduct(const edm::ParameterSet&);
	virtual ~TestGenInfoProduct();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag genrunCollection_;
    edm::InputTag genevtCollection_;

};

#endif
