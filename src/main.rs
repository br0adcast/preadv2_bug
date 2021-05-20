use tokio::io::AsyncReadExt;
use std::env;


#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = env::args().collect();
    let mut file = tokio::fs::File::open(&args[1]).await?;

    let mut contents = vec![];
    file.read_to_end(&mut contents).await?;
    println!("File size = {}", contents.len());
    Ok(())
}

