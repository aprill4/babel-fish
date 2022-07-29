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
define i32 @whileIf() {
whileIf8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 0, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 0, i32* %v12
  %v17 = load i32, i32* %v9
  %bool_19 = icmp slt i32 %v17, 100
  %bool_21 = icmp ne i1 %bool_19, false
  br i1 %bool_21, label %while_entry15, label %next_entry16
while_entry15:
  %v25 = load i32, i32* %v9
  %bool_27 = icmp eq i32 %v25, 5
  br i1 %bool_27, label %if_true_entry22, label %if_false_entry23
next_entry16:
  %v42 = load i32, i32* %v12
  ret i32 %v42
if_true_entry22:
  store i32 25, i32* %v12
  br label %next_entry24
if_false_entry23:
  %v32 = load i32, i32* %v9
  %bool_34 = icmp eq i32 %v32, 10
  br i1 %bool_34, label %if_true_entry29, label %if_false_entry30
next_entry24:
  %v39 = load i32, i32* %v9
  %v41 = add nsw i32 %v39, 1
  store i32 %v41, i32* %v9
  br i1 %bool_21, label %while_entry15, label %next_entry16
if_true_entry29:
  store i32 42, i32* %v12
  br label %next_entry31
if_false_entry30:
  %v36 = load i32, i32* %v9
  %v38 = mul i32 %v36, 2
  store i32 %v38, i32* %v12
  br label %next_entry31
next_entry31:
  br label %next_entry24
}
define i32 @main() {
main43:
  %v44 = call i32 @whileIf()
  ret i32 %v44
}

