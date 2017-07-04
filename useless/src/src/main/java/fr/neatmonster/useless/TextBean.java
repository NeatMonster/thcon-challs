package fr.neatmonster.useless;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.convert.Converter;
import javax.faces.convert.FacesConverter;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import java.io.Serializable;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.cert.X509Certificate;

@ManagedBean
@SessionScoped
public class TextBean implements Serializable {
    private static final long serialVersionUID = 1L;

	static private TrustManager[] getBypassingTrustManager() {
		TrustManager[] certs = new TrustManager[] {
			new X509TrustManager() {
				public X509Certificate[] getAcceptedIssuers() { return null; }
				public void checkClientTrusted(X509Certificate[] certs, String t) {}
				public void checkServerTrusted(X509Certificate[] certs, String t) {}
			}
		};
		return certs;
	}

	static {
		try {
			SSLContext sslCtx = SSLContext.getInstance("SSL");
			TrustManager trustManager[] = getBypassingTrustManager();
			sslCtx.init(null, trustManager, new SecureRandom());
			HttpsURLConnection.setDefaultSSLSocketFactory(sslCtx.getSocketFactory());
		} catch (NoSuchAlgorithmException e) {} catch (KeyManagementException e) {}
	}

	public static class Theme implements Serializable {
        private static final long serialVersionUID = 1L;

	    private String path;

        public Theme(String path) {
            this.path = path;
        }

        @Override
        public String toString() {
            return path;
        }

        @Override
        public boolean equals(Object obj) {
            String path = null;
            if (obj instanceof Theme)
                path = ((Theme) obj).path;
            if (obj instanceof String)
                path = (String) obj;
            if (("light.xhtml".equals(this.path) || "dark.xhtml".equals(this.path))
                    && (!"light.xhtml".equals(path) && !"dark.xhtml".equals(path)))
                return true;
            if (("light.xhtml".equals(path) || "dark.xhtml".equals(path))
                    && (!"light.xhtml".equals(this.path) && !"dark.xhtml".equals(this.path)))
                return true;
            return path != null && this.path.equals(path);
        }
    }

    @FacesConverter("ThemeConverter")
    public static class ThemeConverter implements Converter {

        public ThemeConverter() {}

        @Override
        public Object getAsObject(FacesContext context, UIComponent component, String value) {
            return new Theme(value);
        }
        @Override
        public String getAsString(FacesContext context, UIComponent component, Object value) {
            return value.toString();
        }
    }

	private String text  = "Example";
    private Theme  theme = new Theme("light.xhtml");

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getUppercase() {
        return text.toUpperCase();
    }

    public String getLowercase() {
        return text.toLowerCase();
    }

    public String getVowels() {
        return text.replaceAll("[^aeiouyAEIOUY]", "");
    }

    public String getConsonants() {
        return text.replaceAll("[aeiouyAEIOUY]", "");
    }

    public String getReversed() {
        return new StringBuilder(text).reverse().toString();
    }

    public String getLeetSpeak() {
        return text.replaceAll("[oO]", "0").replaceAll("[lL]", "1")
                   .replaceAll("[eE]", "3").replaceAll("[aA]", "4")
                   .replaceAll("[tT]", "7");
    }

	public Theme getTheme() {
		return theme;
	}

	public void setTheme(Theme theme) {
		this.theme = theme;
	}
}