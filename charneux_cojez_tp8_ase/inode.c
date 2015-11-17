#include "inode.h"
#include "drive.h"

void read_inode (unsigned int inumber, struct inode_s *inode){
    read_bloc_n(inumber, inode, sizeof(inode));
}
void write_inode (unsigned int inumber, const struct inode_s *inode){
    write_inode(inumber, inode, sizeof(inode));
}

unsigned int create_inode(enum file_type_e type){
    unsigned inumber, i;
    struct inode_s inode;
    inode.inode_type = type;
    inode.inode_size = 0;
    for(i = 0; i<NBDIRECT; i++)
        inode.inode_direct[i] = 0;
    inode.inode_indirect = 0;
    inode.inode_2Xindirect = 0;
    inumber = new_bloc();
    if(inumber == 0)
        return 0;
    write_inode(inumber, &inode);
    return inumber;
} 

void free_blocs(unsigned table[], unsigned size){
    int i;
    for(i=0; i<size; i++)
        free_bloc(table[i]);
}

int delete_inode(unsigned int inumber){
    struct inode_s inode;
    unsigned bloc[NBBLOCPARBLOC], bbloc[NBBLOCPARBLOC];
    unsigned i;
    read_inode(inumber, &inode);
    free_bloc(inumber);
    freeblocs(inode.inode_direct, NBDIRECT);
    if(inode.inode_indirect != 0){
        read_bloc_n(inode.inode_indirect, &bloc, NBBLOCPARBLOC * sizeof(unsigned));        
        free_blocs(bloc, NBBLOCPARBLOC);
        free_bloc(inode.inode_indirect);
    }
    if(inode.inode_2Xindirect != 0){
        read_bloc_n(inode.inode_2Xindirect, &bbloc, NBBLOCPARBLOC * sizeof(unsigned));
        for(i=0; i<NBBLOCPARBLOC; i++){
            if(bbloc[i] != 0){
                read_bloc_n(bbloc[i], &bloc, NBBLOCPARBLOC * sizeof(unsigned));        
                free_blocs(bloc, NBBLOCPARBLOC);
                free_bloc(bbloc[i]);
            } 
        }
        free_bloc(inode.inode_2Xindirect);
    }
}

unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc, bool_t do_allocate); 
