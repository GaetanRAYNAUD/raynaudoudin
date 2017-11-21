#include "LoadCommand.h"

namespace engine {

    LoadCommand::LoadCommand(const std::string fileName) : fileName(fileName) {
        
    }

    void LoadCommand::execute(state::State& state) {
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

}
