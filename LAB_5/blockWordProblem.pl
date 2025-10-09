% Block World Problem in Prolog
:- initialization(main).

% ----- Initial and Goal States -----
initial_state([
    on(a, b),
    on(b, c),
    ontable(c),
    clear(a),
    handempty
]).

goal_state([
    on(b, a),
    on(c, b),
    ontable(a),
    clear(c),
    handempty
]).

% ----- Move Definitions -----
move(pickup(X),
    [ontable(X), clear(X), handempty | Rest],
    [holding(X) | Rest]).

move(putdown(X),
    [holding(X) | Rest],
    [ontable(X), clear(X), handempty | Rest]).

move(unstack(X, Y),
    [on(X, Y), clear(X), handempty | Rest],
    [holding(X), clear(Y) | Rest]).

move(stack(X, Y),
    [holding(X), clear(Y) | Rest],
    [on(X, Y), clear(X), handempty | Rest]).

% ----- Goal Check -----
goal(State) :-
    goal_state(Goal),
    subset(Goal, State).

% ----- Planner -----
plan(State, Goal, _, []) :-
    subset(Goal, State).

plan(State, Goal, Visited, [Move | Moves]) :-
    move(Move, State, NewState),
    \+ member(NewState, Visited),
    plan(NewState, Goal, [NewState | Visited], Moves).

% ----- Main Entry -----
main :-
    initial_state(Init),
    goal_state(Goal),
    write('Initial State: '), write(Init), nl,
    write('Goal State: '), write(Goal), nl,
    plan(Init, Goal, [Init], Moves),
    nl, write('Sequence of Moves:'), nl,
    print_moves(Moves).

% ----- Output Helper -----
print_moves([]).
print_moves([M | Rest]) :-
    write(' -> '), write(M), nl,
    print_moves(Rest).


