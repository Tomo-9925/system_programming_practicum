#!/bin/csh -f

echo "# foreach文"
echo ""

echo "  |  1  2  3  4  5  6  7  8  9"
echo "--|---------------------------"
foreach i (1 2 3 4 5 6 7 8 9)
  echo -n " $i|"
  foreach j (1 2 3 4 5 6 7 8 9)
    @ seki = $i
    @ seki *= $j
    printf "%3d" $seki
  end
  echo ""
end
echo "--|---------------------------"

echo ""
echo "# while文"
echo ""

echo "  |  1  2  3  4  5  6  7  8  9"
echo "--|---------------------------"
@ i = 1
while($i<10)
    echo -n " $i|"
    @ j=1
    while($j<10)
        @ seki = $i
        @ seki *= $j
        printf "%3d" $seki
        @ j++
    end
    echo ""
    @ i++
end
echo "--|---------------------------"