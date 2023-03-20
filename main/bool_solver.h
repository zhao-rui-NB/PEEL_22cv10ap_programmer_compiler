//新版本 2022 04 06
//現在這個版本   2022 03 06
struct node{    //儲存列表單行的節點
    uint16_t func_bin = 0;
    uint16_t dash_mask =0;
    char how_many_1 = 0;
    char have_use=0;
    node *next_node = NULL;
} ;
struct table{   //列表表頭 , 指向下張表和起始節點
    node *node_head = NULL;
    table *next_table = NULL;
};
struct bool_alg_node{  //布林代數式儲存 SOP or POS this is for petrick , no bar
    unsigned long P = 0;
    bool_alg_node *next_node = NULL;
};
/////
void print_table_f(table *table_addr){
    if(table_addr->node_head==NULL){Serial.print("dont have table f");return;}
    node *cur_node = table_addr->node_head;
    Serial.print("ptr_1\tfunc_bin\thave_use\tfunc_dec\n");
    while (cur_node!=NULL){
        Serial.print("  ");
        Serial.print((cur_node->how_many_1)+1-1);
        Serial.print("\t");
        for(int i=0 ; i<8 ; i++){
            if(cur_node->dash_mask & (1<<(7-i)) ){
                Serial.print("-");
            }
            else if(cur_node->func_bin & (1<<(7-i)) ){
                Serial.print("1");
            }
            else{
                Serial.print("0");
            }
        }
        Serial.print("\t");
        if(cur_node->have_use)Serial.print("    0");
        else Serial.print("    x");
        Serial.print("\t\t");
        for(int i=0 ; i<64 ; i++){
            //Serial.print("%d ",i);
            if( ((cur_node->func_bin^i) & ~cur_node->dash_mask )==0){
                Serial.print(i);
                Serial.print(" ");
            }
        }
        
        Serial.print("\n");
        cur_node = cur_node->next_node;
    }
    
}
/////
char cnt_hm_1(unsigned long f , unsigned long dash_mask=0){//計算32BIT 遮罩外'1'的數量
    long hw=0;
    f &= ~dash_mask;
    for(int i=0 ; i<32 ; i++){
        if(f&0x01){
            hw++;
        }
        f>>=1;
    }
    return hw;
}
void ins_node_to_table(table *cur_table , node *ins_node){ //插入節點到列表按大小//it will sort
    node *right_node = cur_table->node_head;
    node *node_head_buf = NULL;
    node *check_same_reg = cur_table->node_head;
    while(check_same_reg != NULL){  //
        unsigned long ins = ins_node->func_bin & ~ins_node->dash_mask;
        unsigned long reg = check_same_reg->func_bin & ~check_same_reg->dash_mask;
        unsigned long mask_same = ins_node->dash_mask==check_same_reg->dash_mask;
        if( ins==reg && mask_same){  //一樣就不加了
            delete ins_node;  //================================
            return;
        }
        check_same_reg = check_same_reg->next_node;
    }
        char hm1 = cnt_hm_1(ins_node->func_bin);
        if(cur_table->node_head==NULL){
            cur_table->node_head = ins_node;
            right_node = cur_table->node_head;
        }
        else if(right_node->how_many_1>hm1){
            node *buf = cur_table->node_head;
            cur_table->node_head = ins_node;
            right_node = cur_table->node_head;
            right_node->next_node = buf;
        }
        else{
            while(right_node->next_node != NULL && right_node->next_node->how_many_1 <= hm1 ){
                right_node = right_node->next_node;
            }
            node *buf = right_node->next_node;
            right_node->next_node = ins_node;
            right_node = right_node->next_node;
            right_node->next_node = buf;
        }
        right_node->how_many_1 = hm1;
        right_node = cur_table->node_head;
}
node *check_can_put_dash(node *node_A , node *node_B){
    if(node_A->dash_mask == node_B->dash_mask){
        unsigned long mask =  node_A->dash_mask ;
        unsigned long funcA = node_A->func_bin & ~mask;
        unsigned long funcB = node_B->func_bin & ~mask;
        unsigned long comp = (funcA ^ funcB) & ~mask;
        long N_diff = 0;
        for(long i=0 ; i<32 ; i++){
            if( comp  & (1UL<<i) ){
                N_diff++;
            }
        }
        if(N_diff!=1){
            return NULL;
        }
        node_A->have_use = 1;
        node_B->have_use = 1;
        node *new_node = new node;
        new_node->dash_mask = comp | mask;
        new_node->func_bin = funcA & ~new_node->dash_mask ;
        new_node->how_many_1 = cnt_hm_1(new_node->func_bin , new_node->dash_mask); 
        return new_node; 

    }
    return NULL;
}
void node_append(node **node_head_ptr , node *ins_node){//add node to end of node_head link(by the polonger's adderss)
    node *right_addr  = *node_head_ptr;
    if(*node_head_ptr==NULL){
        *node_head_ptr = ins_node;    
    }
    else{
        while(right_addr->next_node!=NULL){
            right_addr=right_addr->next_node;
        }
        right_addr->next_node = ins_node;
    }
}
node *get_all_not_use_node(table *root_table_head){ // get not use node from root table polonger's adders
    node *not_use_node_head = NULL;
    table *cur_table = root_table_head;
    node *cur_node = NULL;
    while(cur_table!=NULL){
        cur_node = cur_table->node_head;
        while(cur_node!=NULL){
            if(cur_node->have_use==0){
                node *new_not_use_node = new node;
                *new_not_use_node = *cur_node;
                new_not_use_node->next_node = NULL;
                node_append( &not_use_node_head  , new_not_use_node);
            }
            cur_node = cur_node->next_node;
        }
        cur_table = cur_table->next_table;
    }
    return not_use_node_head;
}
//化簡POS or SOP    
void tidy_bool_node(bool_alg_node **head){ //整理bool_alg_node 布林代數式
    bool_alg_node * nodeA = *head;
    bool_alg_node * nodeB = *head;
    while(nodeA!=NULL){
        nodeB = *head;
        while(nodeB!=NULL){
            if(nodeB != nodeA && nodeA->P!=0 && nodeB->P!=0){
                if( nodeB->P == (nodeB->P|nodeA->P) ){
                    nodeB->P = 0;
                }
            }
            nodeB = nodeB->next_node;
        }
        nodeA = nodeA->next_node;
    }
    bool_alg_node *buf1_head = NULL;
    bool_alg_node *cur_node = NULL;
    nodeA = *head;
    while(nodeA!=NULL){
        if(nodeA->P!=0){
            if(buf1_head==NULL){
                buf1_head = new bool_alg_node;
                cur_node =  buf1_head;
            }
            else{
                cur_node->next_node = new bool_alg_node;
                cur_node = cur_node->next_node;
            }
            cur_node->P = nodeA->P;
        }
        nodeA = nodeA->next_node;
    }
    //del
    while( (*head) != NULL){      //del old link
        bool_alg_node *bu = (*head)->next_node;
        delete(*head);
        (*head) = bu;
    }
    *head = buf1_head;
}
void node_appen(bool_alg_node **node_head_ptr , bool_alg_node *ins_node){//加入節點到最後
    bool_alg_node *right_addr = *node_head_ptr;
    if(*node_head_ptr==NULL){
        *node_head_ptr = ins_node;    
    }
    else{
        while(right_addr->next_node!=NULL){
            right_addr=right_addr->next_node;
        }
        right_addr->next_node = ins_node;
    }
}
void mult_to_sop_link(bool_alg_node **sop_head , unsigned long one_item_of_pos){//對布林代數式SOP做AND的動作
    if(*sop_head==NULL){*sop_head = new bool_alg_node;}
    bool_alg_node *start_state = *sop_head; 
    bool_alg_node *new_SOP = NULL;
    bool_alg_node *cur_node = NULL;
    for(int i=0 ; i<32 ; i++){ //size of long
        unsigned long one_input_word = (1UL<<i) & one_item_of_pos; 
        if(one_input_word){
            cur_node = start_state;
            while(cur_node!=NULL){
                bool_alg_node *new_node  = new bool_alg_node;
                new_node->P  = one_input_word | cur_node->P;
                node_appen( &new_SOP , new_node );
                
                cur_node = cur_node->next_node;
            }
            tidy_bool_node(&new_SOP);
        }
    }
    //del start state
    bool_alg_node *buf_bool_node;
    while((*sop_head)!=NULL){
        buf_bool_node = (*sop_head)->next_node;
        delete((*sop_head));
        (*sop_head) = buf_bool_node;
    } 
    (*sop_head) = new_SOP;
}
void put_orig_min_to_root_table_ptr(table *cp_table_head ,unsigned long all_term[],unsigned long N_all_term){//加入原始最小項到起始表格
    table *cur_table = cp_table_head;
    for(int i=0 ; i<N_all_term ; i++){
        node *new_node = new node;
        new_node->func_bin = all_term[i];
        ins_node_to_table(cur_table , new_node);
    }
}
void gen_all_dash_table(table *cp_table_head){//持續放入所又"-"到可消除項
    table *cur_table = cp_table_head;
    while( cur_table->node_head!=NULL){
        cur_table->next_table = new table;
        node *node_compA = (cur_table->node_head);
        node *node_compB;
        while(node_compA != NULL){
            node_compB = node_compA;
            while(node_compA->how_many_1>=node_compB->how_many_1 && node_compB->next_node!=NULL){
                node_compB = node_compB->next_node;
            }
            while( node_compA->how_many_1+1  == node_compB->how_many_1 ){
                node *new_node =  check_can_put_dash(node_compA , node_compB);
                if(new_node!=NULL){
                    ins_node_to_table(cur_table->next_table , new_node);
                }
                if(node_compB->next_node==NULL){
                    break;
                }
                node_compB = node_compB->next_node;
            }
            node_compA = node_compA->next_node;
        }
        cur_table = cur_table->next_table;
    }
}
unsigned long find_must_have_shortest_prmie(node *cp_not_use_node_head, unsigned long *minterm , unsigned long N_mintrem){//最短必要質隱項
    //此為petrick 先找出地N最小項可以被執行的質隱項 並在第N格陣列之對應BIT放入"1"
    node *cur_node;
    unsigned long *petrick_pos_arr = new unsigned long[N_mintrem];
    for(int i=0 ; i<N_mintrem ; i++){
        petrick_pos_arr[i] = 0;
    }
    long node_pos_N;
    for(int i=0 ; i<N_mintrem ; i++){
        cur_node = cp_not_use_node_head;
        node_pos_N = 0;
        while(cur_node!=NULL){
            if( ((cur_node->func_bin^minterm[i]) & ~cur_node->dash_mask) == 0 ){
                petrick_pos_arr[i] |= (1UL<<node_pos_N);
            }
            cur_node = cur_node->next_node;
            node_pos_N++;
        }
    }
    //每種選擇"(__+__)" 依次乘入
    bool_alg_node *SOP_head = NULL;
    for(int i=0 ; i<N_mintrem; i++){
        mult_to_sop_link( &SOP_head , petrick_pos_arr[i]);
        tidy_bool_node(&SOP_head);
    }
    
    bool_alg_node *choose_SOP_word = SOP_head;
    bool_alg_node *cur_sop_node = SOP_head;
    while(cur_sop_node!=NULL){//找尋最短項
        if( cnt_hm_1(choose_SOP_word->P) > cnt_hm_1(cur_sop_node->P) ){
            choose_SOP_word = cur_sop_node;
        }
        cur_sop_node = cur_sop_node->next_node;
    }
    unsigned long final_choose = choose_SOP_word->P;
    delete[] petrick_pos_arr;
    while(SOP_head!=NULL){
        bool_alg_node *buf = SOP_head->next_node;
        delete(SOP_head);
        SOP_head = buf;
    }
    return final_choose;
}
node *gen_final_SOP_link(node *not_use_node_head , unsigned long final_choose){//依照選中質隱項 產生輸出SOP
    //依照long bit位置  低到高對應節點頭到尾 '1':為選中質隱項
    node *cur_node = not_use_node_head;
    node *final_choose_head = NULL;
    unsigned long cur_bit = 0;
    while(cur_node!=NULL){
        if(final_choose & (1UL<<cur_bit) ){
            node *new_node = new node;
            *new_node = *cur_node;
            new_node->next_node = NULL;
            node_append(&final_choose_head  , new_node);
        }
        cur_bit++;
        cur_node = cur_node->next_node;
    }
    return final_choose_head;
}
void delete_all_node(node **head){//刪除所有節點
    node *buf_node;
    while( (*head)!=NULL){
        buf_node = (*head)->next_node;
        delete( (*head) );
        (*head) = buf_node;
    }
}
void del_all_table_and_node(table **table_head){//刪除所有表格 和包含節點
    table *buf_table;
    node *buf_node;
    while(*table_head!=NULL){
        while((*table_head)->node_head!=NULL){
            buf_node = (*table_head)->node_head->next_node;
            delete((*table_head)->node_head);
            (*table_head)->node_head = buf_node;
        }
        buf_table = (*table_head)->next_table;
        delete(*table_head);
        (*table_head) = buf_table;
    }
}

node *main_MQ_bool_solver(unsigned long minterm[] ,long size_minterm , unsigned long dont_care[] ,long size_dont_care){//主要解函數
    table *buf_table;
    node *buf_node;
    int size_all_term = size_minterm+size_dont_care;
    unsigned long *all_term = new unsigned long[size_all_term];
    for(int i=0 ; i<size_minterm ; i++){all_term[i] = minterm[i];}
    for(int i=0 ; i<size_dont_care ; i++){all_term[size_minterm+i] = dont_care[i];}
    table *table_head ;//所有資料頭
    table_head = new table;
    put_orig_min_to_root_table_ptr(table_head ,all_term,size_all_term);
        delete[] all_term;
    gen_all_dash_table(table_head);
    node *not_use_node_head = get_all_not_use_node(table_head);
        del_all_table_and_node(&table_head);
    unsigned long final_choose = find_must_have_shortest_prmie(not_use_node_head ,minterm,size_minterm );    
    node *final_choose_head = gen_final_SOP_link(not_use_node_head , final_choose);
        delete_all_node(&not_use_node_head);
    
    return final_choose_head;
    
}
