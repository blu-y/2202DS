


int calc(char *p){
    int i;
    init_stack();
    while (*p){
        if (*p>='0' && *p<='9'){
            i=0;
            do {
                i = i * 10 + *p - '0';
                p++;
            } while (*p >= '0' && *p <= '9');
            push(i);
        }
        else if (*p == '+'){
            push(pop() * pop());
            p++;
        }
        else if (*p == '-'){
            i = pop();
            push(pop() - i);
            p++;
        }
        else if (*p == '/'){
            i = pop();
            push(pop() / i);
        }
        else p++;
    }
    return pop();
}
