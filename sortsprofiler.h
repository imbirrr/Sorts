#ifndef SORTSPROFILER_H
#define SORTSPROFILER_H


class SortsProfiler
{
public:
    SortsProfiler();
    ~SortsProfiler();

    void comparison();
    void swap();
    void reset();

private:
    unsigned int swaps;
    unsigned int comparisons;
};

#endif // SORTSPROFILER_H
