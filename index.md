---
title: TartanIMU
subtitle: "A Light Foundation Model for Inertial Positioning in Robotics"
layout: page
show_sidebar: false
hide_footer: false
hero_height: is-large
hero_image: img/TartanIMU/FirstPage.png
---

<style>
:root {
    --primary-color: #2c3e50;
    --secondary-color: #3498db;
    --accent-color: #e74c3c;
    --text-color: #2c3e50;
    --bg-color: #ffffff;
    --light-bg: #f8f9fa;
    --border-color: #e9ecef;
}

body {
    font-family: 'Inter', 'Segoe UI', system-ui, -apple-system, sans-serif;
    line-height: 1.6;
    color: var(--text-color);
    background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
    min-height: 100vh;
}

.hero-overlay {
    background: rgba(10, 10, 10, 0.6);
    border-radius: 20px;
    padding: 30px;
    backdrop-filter: blur(10px);
    box-shadow: 0 20px 40px rgba(0,0,0,0.3);
}

.centered-content {
    display: flex;
    flex-direction: column;
    align-items: center;
    text-align: center;
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem;
}

.hero-title {
    font-size: 3.5rem;
    font-weight: 700;
    margin-bottom: 1rem;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    background-clip: text;
    text-shadow: 2px 2px 4px rgba(0,0,0,0.1);
}

.authors {
    font-size: 1.2rem;
    font-weight: 500;
    margin-bottom: 0.5rem;
    color: var(--text-color);
}

.affiliation {
    font-size: 1rem;
    color: #666;
    margin-bottom: 2rem;
}

.button-container {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 15px;
    margin: 2rem 0;
}

.modern-button {
    display: inline-flex;
    align-items: center;
    padding: 12px 24px;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    text-decoration: none;
    border-radius: 50px;
    font-weight: 600;
    transition: all 0.3s ease;
    box-shadow: 0 8px 25px rgba(102, 126, 234, 0.3);
    border: none;
    cursor: pointer;
}

.modern-button:hover {
    transform: translateY(-3px);
    box-shadow: 0 15px 35px rgba(102, 126, 234, 0.4);
    color: white;
    text-decoration: none;
}

.modern-button img, .modern-button i {
    margin-right: 8px;
    width: 20px;
    height: 20px;
}

.content-section {
    background: white;
    border-radius: 20px;
    padding: 3rem;
    margin: 2rem auto;
    max-width: 1200px;
    box-shadow: 0 10px 30px rgba(0,0,0,0.1);
    backdrop-filter: blur(10px);
}

.section-title {
    font-size: 2.5rem;
    font-weight: 700;
    color: var(--primary-color);
    text-align: center;
    margin-bottom: 2rem;
    position: relative;
}

.section-title::after {
    content: '';
    position: absolute;
    bottom: -10px;
    left: 50%;
    transform: translateX(-50%);
    width: 80px;
    height: 4px;
    background: linear-gradient(45deg, #667eea, #764ba2);
    border-radius: 2px;
}

.video-container {
    position: relative;
    border-radius: 15px;
    overflow: hidden;
    box-shadow: 0 15px 35px rgba(0,0,0,0.1);
    margin: 2rem auto;
    max-width: 800px;
}

.video-container iframe {
    width: 100%;
    height: 450px;
    border: none;
}

.figure-container {
    text-align: center;
    margin: 2rem 0;
}

.figure-container img {
    max-width: 100%;
    height: auto;
    border-radius: 15px;
    box-shadow: 0 10px 30px rgba(0,0,0,0.1);
    transition: transform 0.3s ease;
}

.figure-container img:hover {
    transform: scale(1.02);
}

.figure-description {
    margin-top: 1rem;
    font-style: italic;
    color: #666;
    line-height: 1.5;
    max-width: 90%;
    margin-left: auto;
    margin-right: auto;
}

.expandable-section {
    background: white;
    border-radius: 15px;
    margin: 2rem 0;
    overflow: hidden;
    box-shadow: 0 5px 20px rgba(0,0,0,0.08);
    transition: all 0.3s ease;
}

.expandable-section:hover {
    box-shadow: 0 8px 30px rgba(0,0,0,0.12);
}

.expandable-header {
    background: linear-gradient(135deg, #f8f9fa 0%, #e9ecef 100%);
    padding: 1.5rem 2rem;
    cursor: pointer;
    transition: all 0.3s ease;
    border: none;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.expandable-header:hover {
    background: linear-gradient(135deg, #e9ecef 0%, #dee2e6 100%);
}

.expandable-header h2 {
    margin: 0;
    color: var(--primary-color);
    font-size: 1.5rem;
}

.expandable-content {
    padding: 0 2rem;
    max-height: 0;
    overflow: hidden;
    transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);
}

.expandable-content.active {
    padding: 2rem;
    max-height: 2000px;
}

.arrow {
    transition: transform 0.3s ease;
    font-size: 1.2rem;
    color: var(--secondary-color);
}

.arrow.active {
    transform: rotate(180deg);
}

.carousel-container {
    position: relative;
    max-width: 900px;
    margin: 2rem auto;
    border-radius: 15px;
    overflow: hidden;
    box-shadow: 0 15px 35px rgba(0,0,0,0.1);
}

.carousel {
    display: flex;
    transition: transform 0.5s ease-in-out;
}

.carousel-item {
    flex: 0 0 100%;
    position: relative;
}

.carousel-item video {
    width: 100%;
    height: auto;
    max-height: 500px;
    object-fit: contain;
}

.item-description {
    position: absolute;
    bottom: 0;
    left: 0;
    right: 0;
    background: linear-gradient(transparent, rgba(0,0,0,0.8));
    color: white;
    padding: 2rem 1rem 1rem;
    font-size: 1.1rem;
    font-weight: 600;
    text-align: center;
}

.preview-container {
    display: flex;
    justify-content: center;
    gap: 10px;
    padding: 1rem;
    background: #f8f9fa;
    overflow-x: auto;
}

.preview-image {
    width: 80px;
    height: 50px;
    object-fit: cover;
    border-radius: 8px;
    cursor: pointer;
    opacity: 0.6;
    transition: all 0.3s ease;
    border: 2px solid transparent;
}

.preview-image:hover {
    opacity: 0.9;
    transform: scale(1.05);
}

.preview-image.active {
    opacity: 1;
    border-color: var(--secondary-color);
    transform: scale(1.1);
}

.dataset-table {
    width: 100%;
    border-collapse: collapse;
    margin: 2rem 0;
    background: white;
    border-radius: 10px;
    overflow: hidden;
    box-shadow: 0 5px 15px rgba(0,0,0,0.1);
}

.dataset-table th,
.dataset-table td {
    padding: 1rem;
    text-align: left;
    border-bottom: 1px solid #eee;
}

.dataset-table th {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    font-weight: 600;
}

.dataset-table tr:hover {
    background: #f8f9fa;
}

.citation-box {
    background: #f8f9fa;
    border-left: 4px solid var(--secondary-color);
    padding: 1.5rem;
    margin: 2rem 0;
    border-radius: 0 10px 10px 0;
    font-family: 'Courier New', monospace;
    overflow-x: auto;
}

@keyframes fadeInUp {
    from {
        opacity: 0;
        transform: translateY(30px);
    }
    to {
        opacity: 1;
        transform: translateY(0);
    }
}

.content-section {
    animation: fadeInUp 0.6s ease-out;
}

@media (max-width: 768px) {
    .hero-title {
        font-size: 2.5rem;
    }
    
    .content-section {
        margin: 1rem;
        padding: 2rem 1.5rem;
    }
    
    .modern-button {
        display: block;
        margin: 0.5rem auto;
        width: fit-content;
    }
    
    .button-container {
        flex-direction: column;
        align-items: center;
    }
}

.image-container {
    text-align: center;
    margin: 2rem 0;
}

.image-container img {
    max-width: 100%;
    height: auto;
    border-radius: 15px;
    box-shadow: 0 10px 30px rgba(0,0,0,0.1);
}

.image-caption {
    text-align: center;
    font-style: italic;
    color: #666;
    margin-top: 1rem;
    line-height: 1.5;
}

.equation {
    display: block;
    text-align: center;
    margin: 2rem 0;
    padding: 1rem;
    background: #f8f9fa;
    border-radius: 10px;
    font-size: 1.1rem;
}
</style>

<script>
window.onload = function () {
    let heroTitle = document.querySelector('.hero .title');
    if (heroTitle && heroTitle.parentElement) {
        heroTitle.parentElement.classList.add('hero-overlay');
    }
}
</script>

<div class="centered-content">
    <h1 class="hero-title">TartanIMU: A Light Foundation Model for Inertial Positioning in Robotics</h1>
    <p class="authors">
        Shibo Zhao<sup>1†*</sup>, Sifan Zhou<sup>1†</sup>, Raphael Blanchard<sup>1</sup>, Yuheng Qiu<sup>1</sup>, Wenshan Wang<sup>1</sup>, Sebastian Scherer<sup>1</sup>
    </p>
    <p class="affiliation">
        <sup>†</sup>Equal contribution, <sup>*</sup>Contact Author<br>
        <sup>1</sup>Carnegie Mellon University
    </p>
    <p class="affiliation">
        <b>Code and Dataset Available at CVPR 2025</b>
    </p>
    
    <div class="button-container">
        <a href="https://openaccess.thecvf.com/content/CVPR2025/papers/Zhao_Tartan_IMU_A_Light_Foundation_Model_for_Inertial_Positioning_in_CVPR_2025_paper.pdf" class="modern-button">
            📄 Paper
        </a>
        <a href="https://github.com/superxslam/SuperOdom" class="modern-button">
            💾 Code
        </a>
        <a href="https://huggingface.co/datasets/raphael-blanchard/TartanIMU/tree/main" class="modern-button">
            🤗 Dataset & Checkpoints
        </a>
    </div>
</div>

## Overview Video

<div class="video-container">
    <iframe src="https://www.youtube.com/embed/HqoDL2xiaZA" 
            title="TartanIMU Overview Video" 
            allowfullscreen>
    </iframe>
</div>

## About TartanIMU

<div class="content-section">
    <p>Despite recent advances in deep learning, most existing learning IMU odometry methods are trained on specific datasets, lack generalization, and are prone to overfitting, which limits their real-world application. To address these challenges, we present <strong>TartanIMU</strong>, a foundation model designed for generalizable, IMU-based state estimation across diverse robotic platforms.</p>
    
    <p>Our approach consists of three stages: First, a pre-trained foundation model leverages over 100 hours of multi-platform data to establish general motion knowledge, achieving <strong>36% improvement</strong> in ATE over specialized models. Second, to adapt to previously unseen tasks, we use Low-Rank Adaptation (LoRA), allowing positive transfer with only 1.1M trainable parameters. Finally, to support robotics deployment, we introduce online test-time adaptation, which eliminates the boundary between training and testing, allowing the model to continuously "learn as it operates" at <strong>200 FPS</strong> in real-time.</p>
    
    <div class="figure-container">
        <img src="/img/tartanIMU/FirstPage.png" alt="TartanIMU Overview" />
        <p class="figure-description">
            TartanIMU is to our knowledge the first open-source cross-robot foundation model for pose estimation using solely IMU data.
        </p>
    </div>
</div>

## System Architecture

<div class="content-section">
    <div class="image-container">
        <img src="img/TartanIMU/SystemPipeline.PNG" alt="System Architecture" />
        <p class="image-caption">
            <strong>Figure 1: Three learning stages of TartanIMU.</strong> <strong>(a)</strong> Pretrained IMU Model features a shared backbone to capture generalizable IMU knowledge. <strong>(b)</strong> Efficient Fine-Tuning utilizes an adapter to enable positive transfer for new tasks. <strong>(c)</strong> Online Adaptation employs an adaptive memory buffer to support on-the-fly model updates during deployment.
        </p>
    </div>
</div>

## Method

<div class="expandable-section">
    <div class="expandable-header" onclick="toggleSection(this)">
        <h2>Stage 1: Pretrained IMU Model</h2>
        <span class="arrow">▼</span>
    </div>
    <div class="expandable-content">
        <p>The foundation model leverages multi-platform IMU data to learn generalizable motion patterns across different robotic systems. Our approach uses a shared backbone architecture that captures universal motion dynamics while maintaining platform-specific adaptation capabilities.</p>
        
        <div class="image-container">
            <img src="img/TartanIMU/tsne_viz.PNG" alt="t-SNE visualization" style="width: 70%;" />
            <p class="image-caption">t-SNE visualization of the learned ResNet feature space. Cluster separation across platforms shows the model's ability to learn motion-specific dynamics.</p>
        </div>
    </div>
</div>

<div class="expandable-section">
    <div class="expandable-header" onclick="toggleSection(this)">
        <h2>Stage 2: Efficient Fine-Tuning</h2>
        <span class="arrow">▼</span>
    </div>
    <div class="expandable-content">
        <p>Once the base TartanIMU model is pretrained, we adapt it to unseen robot motions or challenging deployment scenarios using <strong>Low-Rank Adaptation (LoRA)</strong>. This technique introduces only a small number of trainable parameters while freezing the original model, preserving its robust general motion understanding.</p>
        
        <p>LoRA achieves this by reparameterizing weight updates as a low-rank matrix decomposition:</p>
        <div class="equation">
            h = W₀x + ΔWx = W₀x + BAx
        </div>
        
        <p>Here, W₀ is the pretrained weight, and A, B are the small matrices trained for the new task. This structure ensures that learning is efficient, allowing use even with very limited data.</p>
        
        <div class="image-container">
            <img src="img/TartanIMU/Offline_Finetuning.png" alt="Offline finetuning results" />
            <p class="image-caption">Our LoRA-based finetuning improves accuracy on new motion tasks while keeping computational and data costs low.</p>
        </div>
        
        <div class="image-container">
            <img src="img/TartanIMU/no_forgetting.png" alt="No forgetting comparison" style="width: 60%;" />
            <p class="image-caption">Comparison of LoRA vs. full fine-tuning. LoRA retains prior knowledge, while full finetuning can degrade earlier performance.</p>
        </div>
    </div>
</div>

<div class="expandable-section">
    <div class="expandable-header" onclick="toggleSection(this)">
        <h2>Stage 3: Online Adaptation</h2>
        <span class="arrow">▼</span>
    </div>
    <div class="expandable-content">
        <p>In the final stage of our TartanIMU pipeline, we enable real-time test-time adaptation through a novel online learning strategy. Unlike traditional pipelines that maintain a static model during deployment, we allow the model to evolve as it operates.</p>
        
        <div class="image-container">
            <img src="img/TartanIMU/online_adaptation.png" alt="Online adaptation illustration" />
            <p class="image-caption">
                Online adaptation results in an 8-shaped trajectory using only IMU data. By maintaining a balanced buffer across diverse motion segments, TartanIMU adapts quickly during deployment, improving trajectory accuracy over time.
            </p>
        </div>
        
        <div class="image-container">
            <img src="img/TartanIMU/lio_imu_switch_scheme.png" alt="SLAM integration" style="width: 70%;" />
            <p class="image-caption">
                Integration with SLAM pipelines. In clear conditions, LiDAR odometry supervises TartanIMU. When visual degradation occurs, the system switches to TartanIMU predictions until reliability is restored.
            </p>
        </div>
    </div>
</div>

## Results

<div class="content-section">
    <div class="carousel-container">
        <div id="results-carousel" class="carousel">
            <div class="carousel-item">
                <video muted loop playsinline controls>
                    <source src="video/superloc/website_intro3.mp4" type="video/mp4">
                </video>
                <p class="item-description">Quadruped (Foundation Model)</p>
            </div>
            <div class="carousel-item">
                <video muted loop playsinline controls>
                    <source src="video/superloc/website_intro1.mp4" type="video/mp4">
                </video>
                <p class="item-description">Drone (Foundation Model)</p>
            </div>
            <div class="carousel-item">
                <video muted loop playsinline controls>
                    <source src="video/superloc/website_intro2.mp4" type="video/mp4">
                </video>
                <p class="item-description">Human (Foundation Model)</p>
            </div>
            <div class="carousel-item">
                <video muted loop playsinline controls>
                    <source src="video/superloc/website_intro3.mp4" type="video/mp4">
                </video>
                <p class="item-description">UGV (Foundation Model)</p>
            </div>
            <div class="carousel-item">
                <video muted loop playsinline controls>
                    <source src="video/superloc/website_intro3.mp4" type="video/mp4">
                </video>
                <p class="item-description">Off-road Car (Online Adaptation)</p>
            </div>
        </div>
    </div>
    
    <div class="preview-container">
        <img src="img/superloc/preview3.png" alt="Preview 1" class="preview-image active" onclick="showCarouselItem(0)">
        <img src="img/superloc/preview1.png" alt="Preview 2" class="preview-image" onclick="showCarouselItem(1)">
        <img src="img/superloc/preview2.png" alt="Preview 3" class="preview-image" onclick="showCarouselItem(2)">
        <img src="img/superloc/preview3.png" alt="Preview 4" class="preview-image" onclick="showCarouselItem(3)">
        <img src="img/superloc/preview1.png" alt="Preview 5" class="preview-image" onclick="showCarouselItem(4)">
    </div>
</div>

## Dataset

<div class="content-section">
    <p>All datasets from our paper are released with comprehensive ground truth trajectories, calibration files, and sensor data across multiple robotic platforms:</p>
    
    <table class="dataset-table">
        <thead>
            <tr>
                <th>Name</th>
                <th>Source</th>
                <th>Location</th>
                <th>Robot</th>
                <th>Sensor</th>
                <th>Duration</th>
                <th>Rosbag</th>
                <th>GT Trajectory</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>Cave01</td>
                <td>TartanIMU</td>
                <td>Laurel Craven</td>
                <td>Handheld</td>
                <td>RGB,LiDAR,IMU</td>
                <td>838s</td>
                <td><a href="#" class="modern-button">Download</a></td>
                <td><a href="#" class="modern-button">Download</a></td>
            </tr>
            <tr>
                <td>Cave02</td>
                <td>TartanIMU</td>
                <td>Laurel Craven</td>
                <td>Handheld</td>
                <td>RGB,LiDAR,IMU</td>
                <td>986s</td>
                <td><a href="#" class="modern-button">Download</a></td>
                <td><a href="#" class="modern-button">Download</a></td>
            </tr>
        </tbody>
    </table>
    
    <p><strong>Ground truth trajectory</strong> follows <a href="https://github.com/MichaelGrupp/evo/wiki/Formats">TUM</a> format:</p>
    <div class="citation-box">
        timestamp x y z q_x q_y q_z q_w
    </div>
</div>

## Citation

<div class="content-section">
    <div class="citation-box">
@InProceedings{Zhao_2025_CVPR,
    author    = {Zhao, Shibo and Zhou, Sifan and Blanchard, Raphael and Qiu, Yuheng and Wang, Wenshan and Scherer, Sebastian},
    title     = {Tartan IMU: A Light Foundation Model for Inertial Positioning in Robotics},
    booktitle = {Proceedings of the Computer Vision and Pattern Recognition Conference (CVPR)},
    month     = {June},
    year      = {2025},
    pages     = {22520-22529}
}
    </div>
</div>

## Contact

<div class="content-section">
    <p>If you have any questions or want to contribute to this work, please feel free to send email to <strong>Shibo Zhao</strong> (shiboz@andrew.cmu.edu). Thank you! 😊</p>
</div>

<script>
function toggleSection(header) {
    const content = header.nextElementSibling;
    const arrow = header.querySelector('.arrow');
    content.classList.toggle('active');
    arrow.classList.toggle('active');
}

let currentCarouselIndex = 0;

function showCarouselItem(index) {
    const carousel = document.getElementById('results-carousel');
    const previews = document.querySelectorAll('.preview-image');
    const videos = carousel.querySelectorAll('video');
    
    // Update carousel position
    carousel.style.transform = `translateX(-${index * 100}%)`;
    
    // Pause all videos and play current
    videos.forEach(video => {
        video.pause();
        video.currentTime = 0;
    });
    videos[index].play().catch(e => console.error("Error playing video:", e));
    
    // Update preview images
    previews.forEach((img, i) => {
        img.classList.toggle('active', i === index);
    });
    
    currentCarouselIndex = index;
}

// Initialize carousel
document.addEventListener('DOMContentLoaded', function() {
    showCarouselItem(0);
});

// Auto-expand first method section
document.addEventListener('DOMContentLoaded', function() {
    const firstHeader = document.querySelector('.expandable-header');
    if (firstHeader) {
        toggleSection(firstHeader);
    }
});
</script> 