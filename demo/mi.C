// Multiple inheritance: does cfront need this-adjustment / thunks?
struct IPersist {
    virtual int  GetClassID();
};

struct IService {
    virtual int  QueryService();
};

class CSample : public IPersist, public IService {
    long m_cRef;
public:
    int GetClassID()    { return 1; }
    int QueryService()  { return 2; }
};

int main()
{
    CSample* c = new CSample;
    IPersist* p = c;      // points at the object base
    IService* q = c;      // MUST point past IPersist's vptr
    return p->GetClassID() + q->QueryService();
}
