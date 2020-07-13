      DOUBLE PRECISION FUNCTION DAIKEI(A,B,DIV_NUM)
      DOUBLE PRECISION A, B
      DOUBLE PRECISION H, ANS
      DOUBLE PRECISION CURRENT, NEXT
      INTEGER*4 DIV_NUM
      INTEGER I

      H = (B-A) / DIV_NUM
      I = 0
      ANS = 0

      CURRENT = sin((A+H*I)/2) + cos(2*(A+H*I))
      DO WHILE (I < DIV_NUM)
        NEXT = sin((A+H*I+H)/2) + cos(2*(A+H*I+H))
        ANS = ANS + ( CURRENT + NEXT ) * H / 2
        CURRENT = NEXT
        I = I + 1
      END DO

      DAIKEI=ANS
      RETURN
      END