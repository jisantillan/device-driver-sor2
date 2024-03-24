#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/uaccess.h>  
      
#define DEVICE_NAME "chardevice"
#define MAX_SIZE 1024
#define SUCCESS 0

static unsigned long buffer_size = 0;

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

char mensaje[MAX_SIZE];
int major ;
int device_abierto = 0 ;  // 0 = device cerrado, 1 = device abierto

static struct file_operations fops = {
    	.read = device_read,
        .write = device_write,
        .open = device_open,
        .release = device_release
};

int init_module(void){ //Se invoca cuando se carga el modulo 
	major = register_chrdev(0, DEVICE_NAME, &fops);
        if (major < 0) {
		 pr_info("char-device : Ha ocurrido una falla en el registro del char device\n");
		 return major;
	}
    pr_info("char-device : Se recomienda usar por convención 'sudo mknod /dev/%s c %d 0'", DEVICE_NAME, major);
	pr_info("char-device : Driver registrado con el major number %d\n", major);
	return SUCCESS;
}

void cleanup_module(void){ //Se invoca cuando se descarga el modulo        
	unregister_chrdev(major, DEVICE_NAME);
	pr_info("char-device : Driver desregistrado \n");
}

static int device_open(struct inode *inode, struct file *file){ // Se invoca cuando un proceso trata de abrir el device file
    if (device_abierto){
        return -EBUSY;
	}
    device_abierto++;
    try_module_get(THIS_MODULE);
	pr_info("char-device: Se ha abierto correctamente el device");
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file){ // Se invoca cuando un proceso cierra el device file
    device_abierto--;
    module_put(THIS_MODULE);
	pr_info("char-device: Se ha cerrado el device");
        return SUCCESS;
}

static ssize_t device_read(struct file *file_pointer, char __user *buffer,size_t buffer_length, loff_t *offset){
    int length = sizeof(mensaje);
    ssize_t ret = length;
    if (*offset >= length || buffer_size == 0){
        pr_info("char-device : Se ha leido el dispositivo\n");
        return SUCCESS;
    }
    if (copy_to_user(buffer, mensaje, length))
    {
        return -EFAULT;
    }
    pr_info("char-device : Se ha leido el dispositivo\n");
    *offset += length;

    return ret;
}

static ssize_t device_write(struct file *file, const char __user *buff, size_t len, loff_t *off){
    memset(mensaje, 0, MAX_SIZE); // Limpiamos el buffer
    buffer_size = len;
    if (buffer_size > MAX_SIZE)
    {
        buffer_size = MAX_SIZE;
    }
    if (copy_from_user(mensaje, buff, buffer_size)){
        pr_info("char-device : Se ha escrito en el dispositivo la palabra: %s" , mensaje);	
        return -EFAULT;
    }
    mensaje[buffer_size & (MAX_SIZE - 1)] = '\0';
    *off += buffer_size;
    pr_info("char-device : Se ha escrito en el dispositivo la palabra: %s" , mensaje);	
    return len; 
}
  
MODULE_LICENSE("GPL ");
MODULE_AUTHOR("JAVIER_SANTILLAN");
MODULE_DESCRIPTION("Modulo que devuelve lo último que fue escrito en el dispositivo.");


