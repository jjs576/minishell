# jjoo_yepark_minishell
미완성이라 여기에 올림. 다 만들면 03minishell에 올릴 생각임
### 할 일 목록 (흐름순)
- [x]  구조체 만들기
- [x]  signal 관리
    - [x]  signal 핸들링 함수 구현
        - [ ]  구체적으로!
- [x]  envp 관리
    - [x]  envp 파싱
    - [x]  linkedList로 저장
- [x]  명령줄 입력받기
    - [x]  백슬래시 처리
        - [x]  다음 줄 입력 처리
    - [x]  따옴표 처리
        - [x]  짝맞추기
    - [x]  Ctrl-D 처리
        - [x]  다음 줄에서의 Ctrl-D 처리
- [x]  토큰화
    - [x]  따옴표 처리
    - [x]  공백 처리
    - [x]  백슬래시 처리
    - [x]  따옴표 안에 백슬래시
    - [x]  파이프(|), 세미콜론(;) 처리
- [ ]  파이프, 리다이렉션 처리
- [ ]  명령어 구현
    - [x]  echo
    - [ ]  cd
    - [ ]  export
    - [ ]  unset
    - [ ]  env
    - [ ]  exit
    - [ ]  $?

