#ifndef VERTEX_PRODUCER
#define VERTEX_PRODUCER

#include <cp3_llbb/Framework/interface/Producer.h>

#include <DataFormats/VertexReco/interface/Vertex.h>

class VerticesProducer: public Framework::Producer {
    public:
        VerticesProducer(const std::string& name, const ROOT::TreeGroup& tree, const edm::ParameterSet& config):
            Producer(name, tree, config)
        {

        }

        virtual ~VerticesProducer() {}

        virtual void doConsumes(const edm::ParameterSet& config, edm::ConsumesCollector&& collector) override {
            m_vertices_token = collector.consumes<std::vector<reco::Vertex>>(config.getUntrackedParameter<edm::InputTag>("vertices", edm::InputTag("offlineSlimmedPrimaryVertices")));
        }

        virtual void produce(edm::Event& event, const edm::EventSetup& eventSetup) override;

    private:

        // Tokens
        edm::EDGetTokenT<std::vector<reco::Vertex>> m_vertices_token;

    public:
        // Tree members

        std::vector<float>& normalizedChi2 = tree["normalizedChi2"].write<std::vector<float>>();
        std::vector<float>& ndof = tree["ndof"].write<std::vector<float>>();
        std::vector<bool>& isFake = tree["isFake"].write<std::vector<bool>>();
        std::vector<bool>& isValid = tree["isValid"].write<std::vector<bool>>();
        std::vector<reco::Vertex::Point>& position = tree["position"].write<std::vector<reco::Vertex::Point>>();
        std::vector<reco::Vertex::CovarianceMatrix>& covariance = tree["covariance"].write<std::vector<reco::Vertex::CovarianceMatrix>>();
};

#endif
