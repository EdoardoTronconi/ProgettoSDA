
template <typename Iterator>
class tester {
public:
    virtual void sort(Iterator start, Iterator end) = 0;
    
private:
    int size, trials, randomized, sorted;
};
