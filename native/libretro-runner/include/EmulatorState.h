enum class RuntimeState
{
    Running,
    Paused,
    SaveMenu
};

class EmulatorState
{
public:
    RuntimeState runtimeState =
        RuntimeState::Running;

    std::string currentGameName;

    int currentSaveSlot = 0;
};