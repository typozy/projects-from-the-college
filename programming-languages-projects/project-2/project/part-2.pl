%Firstly, I defined the flies.

fly(edirne,erzurum,5).
fly(erzurum,antalya,2).
fly(antalya,izmir,1).
fly(antalya,diyarbakir,5).
fly(diyarbakir,ankara,8).
fly(izmir,istanbul,3).
fly(izmir,ankara,6).
fly(istanbul,ankara,2).
fly(istanbul,trabzon,3).
fly(trabzon,ankara,6).
fly(ankara,kars,3).
fly(kars,gaziantep,3).

%Then I assigned all the flies to flight bidirectionally.

flight(X,Y,C) :- fly(X,Y,C);fly(Y,X,C).

%Then i used the definition of flight in road recursively
%to find the ways from a given destination to another one.

road(A,B,P,[B|P]) :- flight(A,B,_).

road(A,B,Visited,Path) :-
	flight(A,C,_),
	C \== B,
	\+member(C,Visited),
	road(C,B,[C|Visited],Path).

%And sum calculates the cost for any given path recursively.
%(path is found by road)

sum(_,[],O,N) :- N is O,!.

sum(R,[H|T],O,N) :-
	flight(R,H,C),
	K is O+C,
	sum(H,T,K,N).

%And route uses the definition of road to find a way
%and uses the found way to calculate the cost
%by the definition of sum.

route(A,B,K) :-
	road(A,B,[A],Q),
	reverse(Q,[_|Path]),
	sum(A,Path,0,K).