#include "LoadCommand.h"
#include "json/json.h"

namespace engine {

    LoadCommand::LoadCommand(const std::string fileName) : fileName(fileName) {
        
    }

    void LoadCommand::execute(state::State& state, std::stack<std::shared_ptr<Action>>& actions) {
        state.addEpoch();
        state.getBoard().loadTerrainsFromFile(fileName);
    }

    const std::string& LoadCommand::getFileName() const {
        return fileName;
    }

    CommandTypeId LoadCommand::getTypeId() const {
        return CommandTypeId::LOAD;
    }

    void LoadCommand::setFileName(const std::string& fileName) {
        this->fileName = fileName;
    }

    Command* LoadCommand::clone() const {
        return new LoadCommand(*this);
    }

    void LoadCommand::serialize(Json::Value& out) const {
        Json::Value jsonCommand;
        jsonCommand["Type"] = "LoadCommand";
        jsonCommand["fileName"] = fileName;
        
        out["Commands"].append(jsonCommand);
    }

    LoadCommand* LoadCommand::deserialize(const Json::Value& in) {
        std::string file;
        
        file = in["fileName"].asString();
        
        return new LoadCommand(file);
    }

}
