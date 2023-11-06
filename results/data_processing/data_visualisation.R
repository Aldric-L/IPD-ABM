data <- read.csv("data.csv")

library(ggplot2)

# Full cooperative agents vs full non-cooperative
temp <- data.frame(iteration=numeric(0), agents= numeric(0), is_cooperative= numeric(0))
for (i in data$iteration){
  temp[i*2, ] <- c(data[i, ]$iteration, data[i, ]$fullcoop_agents, 1)
  temp[i*2+1, ] <- c(data[i, ]$iteration, data[i, ]$fulldefector_agents, 0)
}

ggplot(temp, aes(iteration, agents)) +
  geom_point(size = 0.5, aes(color=is_cooperative))
