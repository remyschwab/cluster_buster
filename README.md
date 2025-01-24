# Cluster Buster
A tool for preprocessing sequence databases for [TetRex](https://github.com/remyschwab/TetRex). The `easy-cluster` workflow from [MMseqs2](https://github.com/soedinglab/MMseqs2) can take a large FASTA file as input and will output a clustered FASTA file. `Cluster Buster` will break the MMSeqs2 output into multiple files which can then be indexed by `TetRex`.

By clustering the database given as input to TetRex, it is possible to limit the number of files `TetRex` must perform a linear verification on (which is often one of the slowest steps).

## Compile
Find below an example command to compile `Cluster Buster`.
```shell
g++-14 -lz -o cluster_buster cluster_buster.cpp
```

## Usage
`Cluster Buster` usage takes the form `cluster_buster input_fasta.fa output_directory minimum_cluster_size`
```shell
cluster_buster swissprot_cluster_all_seqs.fasta outdir 50
```

The `minimum_cluster_size` argument ensures that no one file has less than that number of FASTA records. It will not break up a cluster.


## Note
`Cluster Buster` makes use of the `kseq` library from Heng Li!
