#include "inode.h"
#include "drive.h"

void read_inode (unsigned int inumber, struct inode_s *inode){
    read_bloc_n(current_volume, inumber, (unsigned char *) inode, sizeof(inode));
}
void write_inode (unsigned int inumber, const struct inode_s *inode){
    write_bloc_n(current_volume, inumber, (unsigned char *) inode, sizeof(inode));
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
    free_blocs(inode.inode_direct, NBDIRECT);
    if(inode.inode_indirect != 0){
        read_bloc_n(current_volume, inode.inode_indirect, (unsigned char *) &bloc, NBBLOCPARBLOC * sizeof(unsigned));        
        free_blocs(bloc, NBBLOCPARBLOC);
        free_bloc(inode.inode_indirect);
    }
    if(inode.inode_2Xindirect != 0){
        read_bloc_n(current_volume, inode.inode_2Xindirect, (unsigned char *) &bbloc, NBBLOCPARBLOC * sizeof(unsigned));
        for(i=0; i<NBBLOCPARBLOC; i++){
            if(bbloc[i] != 0){
                read_bloc_n(current_volume, bbloc[i], (unsigned char *) &bloc, NBBLOCPARBLOC * sizeof(unsigned));        
                free_blocs(bloc, NBBLOCPARBLOC);
                free_bloc(bbloc[i]);
            } 
        }
        free_bloc(inode.inode_2Xindirect);
    }
    return EXIT_SUCCESS;
}

unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc, bool_t do_allocate){
    struct inode_s inode;
    /*unsigned bloc[NBBLOCPARBLOC], bbloc[NBBLOCPARBLOC];*/
    read_inode(inumber, &inode);
    if(fbloc < NBDIRECT){
        if(do_allocate){
            if(inode.inode_direct[fbloc] == 0){
                inode.inode_direct[fbloc] = new_bloc_zero();
                write_inode(inumber, &inode);
            }
            return inode.inode_direct[fbloc];
        }
    }
    printf("hors limite\n");
    exit(EXIT_FAILURE);
}
