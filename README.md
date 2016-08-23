# Permutations

This small utility generates the complete list of permutations on `S_n = {1, 2, ..., n}`
in ascending lexicographical order. Under the hood there is a re-implementation of 
the STL's `next_permutation()` algorithm which we call **n!-1** times.

This exercise was inspired by the traveling salesman problem. We'd like decompose
large instances of the TSP into subproblems
that can be solved in parallel before being reintegrated into 


Coming soon:
[ ] Redesign in a more object-oriented fashion
  [ ] Create a permutation generator class. Construct and run it once in main().
  [ ] Move global data into object state and make helper functions private.
  [ ] Cleanly separate the next_permutation() functionality from its invocation.
[ ] Make nextPermutation() and generateAllPermutations() public.

