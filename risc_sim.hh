void check_inst(vector<pair<string, string>> instruction_line, struct regs *x, int *pc , int line_number , stack<stack_label> *show_func , struct store_label *label_line , int data_length);


void run(vector<pair<string, string>> instruction_lines, struct regs *x, int *pc, int *breakpoint , stack<stack_label> *show_func , struct store_label *label_line , int data_length);


void step(vector<pair<string, string>> instruction_lines, struct regs *x, int *pc, int *breakpoint , stack<stack_label> *show_func , struct store_label *label_line , int data_length);

void store_in_mem(string int_value, int *mem_adrr, int bytes);
void storing_label(string filename, struct store_label *label_line);

string remove_label(string assembly_instruction, int index, struct store_label *label_line);
string remove_leading_blanks(string assembly_instruction);

vector<pair<string, string>> parse(string filename, struct store_label *label_line, int *data_length);

void print_stack(stack<stack_label> show_func);
void print_mem(int address, int length);
void print_regs(struct regs *x);

void initialize_mem(void);
void initialize_stack(stack<stack_label> *show_func);
void initialize_regs(struct regs *x);
