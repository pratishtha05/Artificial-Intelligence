%state ( Position of monkey H , Position of monkey V , Position of chair , Position of stick , Carry stick? ,Carry chair?, Position of banana V , Position of banana H )

move( state( P, onchair, P, P, carrystick, notcarrychair, banaup, P),
  knock,
          state( P, onchair, P, P, carrystick, notcarrychair, banadown, P) ).


move( state( P, onfloor, P, Z, K, notcarrychair, banaup, B),
           climb,
           state( P, onchair, P, Z, K, notcarrychair, banaup, B) ).


move( state( P, onfloor, P, P, K, carrychair , banaup, P),
           put_chair_down,
           state( P, onfloor, P, P, K, notcarrychair, banaup, P) ).


move( state( P1, onfloor, P1, P1, carrystick, carrychair, banaup, B),
           walk_with_chair_and_stick( P1, P2),
           state( P2, onfloor, P2, P2, carrystick, carrychair, banaup, B) ).


move( state( P, onfloor, Z, P, notcarrystick, K , banaup, B),
           carry_stick,
           state( P, onfloor, Z, P, carrystick,K, banaup, B) ).


move( state( P, onfloor, P, Z, K, notcarrychair, banaup, B),
           carry_chair,
           state( P, onfloor, P, Z, K, carrychair, banaup, B) ).


move( state( P1, onfloor, Z, P1, carrystick, notcarrychair, banaup, B),
            walk_with_stick( P1, P2),
     state( P2, onfloor, Z, P2, carrystick, notcarrychair, banaup, B) ).


move(state(P1, onfloor, P1, Z, notcarrystick, carrychair, banaup, B),
     walk_with_chair(P1, P2),
     state(P2, onfloor, P2, Z, notcarrystick, carrychair, banaup, B)).


move( state( P1, onfloor, Z, K, notcarrystick, notcarrychair, banaup, B),
            walk( P1, P2),
     state( P2, onfloor, Z, K, notcarrystick, notcarrychair, banaup, B) ).


canget( state( _, _, _, _, _,_, banadown, _) ).


canget( State1)  :- move( State1, Move, State2), canget( State2).