#include <iostream>
#include <fstream>
#include <filesystem>
#include <zlib.h>
#include <stdio.h>

#include "kseq.h"  
KSEQ_INIT(gzFile, gzread)

size_t convert_str_to_size(const std::string &min_arg)
{
    std::stringstream sstream(min_arg);
    size_t min_cnt;
    sstream >> min_cnt;
    return min_cnt;
}

int main(int argc, char *argv[])
{
    gzFile fp;
    std::string outdir = argv[2];
    std::filesystem::create_directory(outdir);
    kseq_t *record;
    int l;
    
    // Deal with 
    const size_t min_members = convert_str_to_size(argv[3]);
    size_t member_cnt = min_members; // Pretend like one group has already been made

    // Begin Reading and writing
    std::ofstream cluster_stream;
    fp = gzopen(argv[1], "r");
    record = kseq_init(fp);
    while ((l = kseq_read(record)) >= 0) {
        // std::cout << member_cnt << std::endl;
        if(record->seq.l == 0)
        {
            if(member_cnt >= min_members)
            {
                cluster_stream.close();
                member_cnt = 0;
                std::string cluster_fpath = outdir+"/"+record->name.s+".fa";
                cluster_stream.open(cluster_fpath);
            }
            continue;
        }
        cluster_stream << ">" << record->name.s << std::endl;
        cluster_stream << record->seq.s << std::endl;
        ++member_cnt;
    }
    kseq_destroy(record);
    gzclose(fp);
    return 0;
}
