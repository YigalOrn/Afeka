%Yigal.O , ID:303893416
%-----------------------------------------------------------------

%-----------------------------------------------------------------
%Question_1

%KB
word(astante, a,s,t,a,n,t,e).
word(astoria, a,s,t,o,r,i,a).
word(baratto, b,a,r,a,t,t,o).
word(cobalto, c,o,b,a,l,t,o).
word(pistola, p,i,s,t,o,l,a).
word(statale, s,t,a,t,a,l,e).

%rules
crossword(V1,V2,V3,H1,H2,H3):-

	%Vertical, chosen arbitrarily.
	word(V1,_,V1_2,_,V1_4,_,V1_6,_),
	word(V2,_,V2_2,_,V2_4,_,V2_6,_),
	word(V3,_,V3_2,_,V3_4,_,V3_6,_),

	V1\=V2,V1\=V3,V2\=V3,

	%Horizontal
	word(H1,_,V1_2,_,V2_2,_,V3_2,_),
	word(H2,_,V1_4,_,V2_4,_,V3_4,_),
	word(H3,_,V1_6,_,V2_6,_,V3_6,_),

	H1\=H2,H1\=H3,H2\=H3,

	V1\=H1,V1\=H2,V1\=H3,
	V2\=H1,V2\=H2,V2\=H3,
	V3\=H1,V3\=H2,V3\=H3.



%-----------------------------------------------------------------



%-----------------------------------------------------------------
%Question_2

/*
 *?- mirror(tree(tree(leaf(1), leaf(2)), leaf(4)), T).
 *T = tree(leaf(4), tree(leaf(2), leaf(1))).
 *
 *Taking Dr Hotovely approach(mentioned briefly in class),
 *we dont need to be concerned how the job
 *-one level below i.e. a smaller problem- will be done!
 *we only need to assume that the
 *"workers" will do it correctly upon our request
 *and our task is only to deal with this result.
 *we do need to come up with the base cluase i.e. stop condition.
 *
 *in our case, lets assume that we got two reflected trees from the
 *workers what should we do now?, we should combine them to a one whole
 *tree
*/

%stop condition:
mirror(leaf(Label), leaf(Label)).

%recursion step:
mirror(tree(Left_Tree, Right_Tree), T):-mirror(Left_Tree, T1),mirror(Right_Tree ,T2), T=tree(T2, T1).

%-----------------------------------------------------------------



%-----------------------------------------------------------------
%Question_3

%example: swapFirstLast([1,2,3,4],[4,2,3,1]) should return true.

/*
*For the following solution i got a hint from Ronen...so perhaps i
*didnt solve it by my self. Modus oprndos for (1): each recursion
*step only check the second member of each list, check that they are
*the same. in the base cluse, check that there are two member left from
*each list ensuring this way that the list are of the same length. in
*this final step the two members left from each list should be the same
*crossbreeding!
*/

% 1) for (a)

%base clause
swapFirstLast1([X1,X2], [X2,X1]).

%recursion clause:
swapFirstLast1([H1,Z|T1],[H2,Z|T2]):- swapFirstLast1([H1|T1],[H2|T2]).




%2) for (b)

/*
recursion here invovles using the append predicate.
The logic behind the solotion based on the given example:
L1 = [1,2,3,4], L2 = [4,2,3,1].
When using lists structures we can only get the head and tail of a list
using the | operator easily!, by looking(alot!) at L2 we could come to a
conclusion (regarding the hint!!) that if we had in hand the list
[4,2,3] we only need to concat the head of L1,[1] and compare- via
unification- it to L2...
And we can acheive this by regarding only to the tail of L1 and using
append with dummy varibles!

It was very hard to notice this!
I understand append() and its workhouse including the search tree very
well! and i think Ronen you should do a similiar,if there is, example in
class that will not tell the sol for this one...
*/
swapFirstLastWithAppend([H1|T1], L2):- append(T,[X],T1), append([X|T],[H1], L2).

%-----------------------------------------------------------------










