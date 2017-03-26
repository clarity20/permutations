# Permutations

This small utility generates the complete list of permutations on `S_n = {1, 2, ..., n}`
in ascending lexicographical order. Under the hood there is a re-implementation of 
the STL's `next_permutation()` algorithm which we call **n!-1** times.

This exercise was inspired by the traveling salesman problem. My overall idea is
to decompose large instances of the TSP into a series of subproblems, solve those 
using standard techniques, and reintegrate the solutions into the original problem
to give us a nice roadmap to a good overall solution. What's different about this approach
is the technique by which we identify promising subproblems. We hope that in the near future
we will have the opportunity to pursue this idea at length.


# Todo list:
- [ ] Redesign in a more object-oriented fashion
  - [ ] Create a permutation generator class. Construct and run it once in main().
  - [ ] Move global data into object state and make helper functions private.
  - [ ] Cleanly separate the next_permutation() functionality from its invocation.
- [ ] Make nextPermutation() and generateAllPermutations() public.
- [ ] Explain factoriadic numbers in brief. Give a link to the details.

