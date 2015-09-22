
x = [-1 -2 -3; -2 1 3 ; 4 5 6 ];
result = f_signed(x);


%함수
function result = f_signed(x)
result = sum(x(:)>0);

