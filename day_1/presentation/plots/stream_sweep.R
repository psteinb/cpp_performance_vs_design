
args <- commandArgs(T)
print(args)

myargument <- args[length(args)]
myargument <- sub("-","",myargument)
received_inputfile <- ""

if(length(args)==0){
  cat("No arguments supplied.Exiting\n")
  q(save = False)
}else{
  cat("Received Arguments:\t")
  received_inputfile <- myargument[1]
  print(received_inputfile)
}

bw_data <- read.table(received_inputfile, header = T, sep = ' ')

bw_data["data_size_kB"] <- (bw_data["num_dbl_elements"]*8.)/1024.

head(bw_data)

library(ggplot2)

first_16_mb <- bw_data[ which( bw_data$data_size_kB<(16*1024) ), ]

head(first_16_mb)

p_first_16_mb <- ggplot(first_16_mb, aes(x=data_size_kB, y=bandwidth_mb_per_second))
p_first_16_mb <- p_first_16_mb + geom_point() + scale_y_log10() + ylim(1e4,1.05*max(first_16_mb$bandwidth_mb_per_second))
p_first_16_mb <- p_first_16_mb + xlab("data volume / kB") + ylab("bandwidth / [MB/s]")

output_base <- sub(".data","",received_inputfile)

ggsave(paste(output_base,"_bw_vs_size_first_16_mb.pdf",sep=""),p_first_16_mb)

p_first_16_mb_double_log10 <- p_first_16_mb + scale_x_log10()
ggsave(paste(output_base,"_bw_vs_size_first_16_mb_double_log10.pdf",sep=""),p_first_16_mb_double_log10)
