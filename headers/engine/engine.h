class Engine
{
private:
    /* data */
public:
    Engine() = default;
    ~Engine() = default;

    bool Initialize();
    void Run();
    void ShutDown();
};
