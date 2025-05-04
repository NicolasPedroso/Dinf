document.addEventListener('DOMContentLoaded', () => {
  // Sistema de temas
  const themeToggle = document.getElementById('theme-toggle');
  const html = document.documentElement;

  // Carregar tema salvo
  const savedTheme = localStorage.getItem('theme') || 'dark';
  html.setAttribute('data-theme', savedTheme);
  themeToggle.textContent = savedTheme === 'dark' ? '🌙' : '☀️';

  // Alternador de tema
  themeToggle.addEventListener('click', () => {
    const newTheme = html.getAttribute('data-theme') === 'dark' ? 'light' : 'dark';
    html.setAttribute('data-theme', newTheme);
    themeToggle.textContent = newTheme === 'dark' ? '🌙' : '☀️';
    localStorage.setItem('theme', newTheme);
  });

  // Smooth scroll
  document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
      e.preventDefault();
      const target = document.querySelector(this.getAttribute('href'));
      if (target) {
        target.scrollIntoView({
          behavior: 'smooth',
          block: 'start'
        });
      }
    });
  });

  // Animação dos cards
  const cards = document.querySelectorAll('.card');
  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.style.opacity = '1';
        entry.target.style.transform = 'translateY(0)';
      }
    });
  }, { threshold: 0.1 });

  cards.forEach(card => {
    card.style.opacity = '0';
    card.style.transform = 'translateY(20px)';
    card.style.transition = 'all 0.6s ease-out';
    observer.observe(card);
  });

  // Validação do formulário
  const form = document.querySelector('form');
  // Substitui o comportamento padrão para exibir mensagem de sucesso
  if (form) {
    form.addEventListener('submit', (e) => {
      const recaptchaResponse = grecaptcha.getResponse();
      if (!recaptchaResponse) {
        e.preventDefault();
        alert('Por favor, complete a verificação reCAPTCHA!');
        grecaptcha.reset();
        return;
      }

      e.preventDefault(); // Impede o envio imediato

      const formData = new FormData(form);

      fetch(form.action, {
        method: form.method,
        body: formData,
        headers: {
          'Accept': 'application/json'
        }
      })
      .then(response => {
        if (response.ok) {
          document.getElementById('form-success').style.display = 'block';
          form.reset();
          grecaptcha.reset();
          desabilitarBotao();
        } else {
          alert('Erro ao enviar. Tente novamente mais tarde.');
        }
      })
      .catch(() => alert('Erro de conexão. Tente novamente mais tarde.'));
    });
  }
});

// Funções do reCAPTCHA
function habilitarBotao() {
  document.getElementById('submitBtn').disabled = false;
}

function desabilitarBotao() {
  document.getElementById('submitBtn').disabled = true;
}

// Debug
console.log('Sistema carregado com sucesso!');
if (typeof grecaptcha === 'undefined') {
  console.error('reCAPTCHA não carregado!');
} else {
  console.log('reCAPTCHA carregado:', grecaptcha);
}