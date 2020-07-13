      REAL SWAP,A,B

      A=170.079
      WRITE(6,*) A

      B=SWAP(A)
      WRITE(6,*) B

      A=SWAP(B)
      WRITE(6,*) A

      STOP
      END