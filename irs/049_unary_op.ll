define void @putint(i32 ) {
putint1:
  ret void
}
define void @putch(i32 ) {
putch3:
  ret void
}
define i32 @getint() {
getint4:
  ret i32 0
}
define i32 @getch() {
getch6:
  ret i32 0
}
define i32 @main() {
main8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 10, i32* %v9
  %v15 = load i32, i32* %v9
  %bool_17 = icmp ne i32 %v15, zeroinitializer
  %bool_19 = icmp eq i1 %bool_17, zeroinitializer
  %bool_21 = icmp ne i1 %bool_19, zeroinitializer
  %bool_23 = icmp eq i1 %bool_21, zeroinitializer
  %bool_25 = icmp ne i1 %bool_23, zeroinitializer
  %bool_27 = icmp eq i1 %bool_25, zeroinitializer
  %v29 = sub nsw i1 false, %bool_27
  br i1 %v29, label %if_true_entry12, label %if_false_entry13
if_true_entry12:
  %v32 = sub nsw i32 0, 1
  %v34 = sub nsw i32 0, %v32
  %v36 = sub nsw i32 0, %v34
  store i32 %v36, i32* %v9
  br label %next_entry14
if_false_entry13:
  store i32 0, i32* %v9
  br label %next_entry14
next_entry14:
  %v38 = load i32, i32* %v9
  ret i32 %v38
}

