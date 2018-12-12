{
  fun max(var x: int = 0, var y : int = 0) -> int{
    if (x < y){
      return x;
    } else {
      return y;
    }
  };

  fun scope_disrupt(var x : int = 0) -> bool{
    var x : bool = true;
    return x;
  };

  fun gcd(var n : int = 0, var m : int = 0) -> int{
    var N : int = n;
    var M : int = m;

    while (N != M){
      if (N > M){
        N = N - M;
      }

      else 
      
      {
        M = M - N;
      }
    }
    return N;
  };

  if (gcd(7,11) != 1){
  
  } else {
    ;
  }


  




}
