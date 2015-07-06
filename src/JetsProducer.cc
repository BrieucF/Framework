
#include <cp3_llbb/Framework/interface/JetsProducer.h>

void JetsProducer::produce(edm::Event& event, const edm::EventSetup& eventSetup) {

    edm::Handle<std::vector<pat::Jet>> jets;
    event.getByToken(m_jets_token, jets);

    for (const auto& jet: *jets) {
        if (! pass_cut(jet))
            continue;

        fill_candidate(jet);

        jecFactor.push_back(jet.jecFactor(0));
        area.push_back(jet.jetArea());
        partonFlavor.push_back(jet.partonFlavour());
        hadronFlavor.push_back(jet.hadronFlavour());

        if (jet.hasUserFloat("pileupJetId:fullDiscriminant"))
            puJetID.push_back(jet.userFloat("pileupJetId:fullDiscriminant"));

        vtxMass.push_back(jet.userFloat("vtxMass"));

        auto& btag_discris = jet.getPairDiscri();
        for (auto& btag_discri: btag_discris) {
            // Get branch from tree
            std::vector<float>& branch = tree[btag_discri.first].write<std::vector<float>>();
            branch.push_back(btag_discri.second);
        }
    }
}