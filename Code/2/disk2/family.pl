% Facts
parent(alice, bob).       % Alice is Bob's parent
parent(bob, carol).       % Bob is Carol's parent
parent(alice, dave).      % Alice is Dave's parent

% Rules
grandparent(X, Y) :-
  parent(X, Z),
  parent(Z, Y).

% X is a grandparent of Y if X is a parent of Z, and Z is a parent of Y.

% Queries
% grandparent(alice, carol).  % Is Alice a grandparent of Carol?
% ?- grandparent(alice, dave).   % Is Alice a grandparent of Dave?
% ?- parent(bob, carol).         % Who is Carol's parent?


