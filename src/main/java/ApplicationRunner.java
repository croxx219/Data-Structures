import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class ApplicationRunner {
    private static final Logger LOGGER = LogManager.getLogger(ApplicationRunner.class.getName());

    public static void main(String[] args) {
        LOGGER.info("--------------- STARTING PROGRAM ---------------");
    }
}
