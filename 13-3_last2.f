      DOUBLE PRECISION FUNCTION DAIKEI(A,B)
      DOUBLE PRECISION A, B
      DOUBLE PRECISION H, ANS
      DOUBLE PRECISION CURRENT, NEXT
      INTEGER DIV_NUM
      INTEGER I

      DIV_NUM = 100000
      H = (B-A) / DIV_NUM
      I = 0
      ANS = 0

      CURRENT = cos(A+H*I)
      DO WHILE (I < DIV_NUM)
        NEXT = cos(A+H*I+H)
        ANS = ANS + ( CURRENT + NEXT ) * H / 2
        CURRENT = NEXT
        I = I + 1
      END DO

      DAIKEI=ANS
      RETURN
      END